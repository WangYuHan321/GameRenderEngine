#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "MeshLoader.h"
#include "../../Shader/Texture.h"

#include "../../Mesh/Material.h"
#include "../../Mesh/Mesh_ID.h"
#include "../../Mesh/Mesh.h"
#include"../../Resource/ResourceManager.h"
#include "../../Scene/SceneNode.h"
#include "../../Scene/Scene.h"

void MeshLoader::Clean()
{
    for (unsigned int i = 0; i < MeshLoader::meshStore.size(); ++i)
    {
        delete MeshLoader::meshStore[i];
    }
}

SceneNode* MeshLoader::LoadMesh(std::string path, bool setDefaultMaterial)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return nullptr;
    }

    std::string directory = path.substr(0, path.find_last_of("/"));

    return MeshLoader::processNode(scene->mRootNode, scene, directory, setDefaultMaterial);
}

SceneNode* MeshLoader::processNode(aiNode* aNode, const aiScene* aScene, std::string directory, bool setDefaultMaterial)
{
    SceneNode* node = new SceneNode(0);

    for (unsigned int i = 0; i < aNode->mNumMeshes; ++i)
    {
        glm::vec3 boxMin, boxMax;
        aiMesh* assimpMesh = aScene->mMeshes[aNode->mMeshes[i]];
        aiMaterial* assimpMat = aScene->mMaterials[assimpMesh->mMaterialIndex];
        Mesh* mesh = MeshLoader::parseMesh(assimpMesh, aScene, boxMin, boxMax);
        Material* material = nullptr;
        if (setDefaultMaterial)
        {
            material = MeshLoader::parseMaterial(assimpMat, aScene, directory);
        }

        if (aNode->mNumMeshes == 1)
        {
            node->Mesh = mesh;
            if (setDefaultMaterial)
            {
                node->Material = material;
            }
            node->m_BoxMin = boxMin;
            node->m_BoxMax = boxMax;
        }
        else
        {
            SceneNode* child = new SceneNode(0);
            child->Mesh = mesh;
            child->Material = material;
            child->m_BoxMin = boxMin;
            child->m_BoxMax = boxMax;
            node->AddChild(child);
        }
    }

    for (unsigned int i = 0; i < aNode->mNumChildren; ++i)
    {
        node->AddChild(MeshLoader::processNode(aNode->mChildren[i], aScene, directory, setDefaultMaterial));
    }

    return node;
}

Mesh* MeshLoader::parseMesh(aiMesh* aMesh, const aiScene* aScene, glm::vec3& out_Min, glm::vec3& out_Max)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    std::vector<unsigned int> indices;

    positions.resize(aMesh->mNumVertices);
    normals.resize(aMesh->mNumVertices);
    if (aMesh->mNumUVComponents[0] > 0)
    {
        uv.resize(aMesh->mNumVertices);
        tangents.resize(aMesh->mNumVertices);
        bitangents.resize(aMesh->mNumVertices);
    }

    indices.resize(aMesh->mNumFaces * 3);

    glm::vec3 pMin(99999.0);
    glm::vec3 pMax(-99999.0);

    for (unsigned int i = 0; i < aMesh->mNumVertices; ++i)
    {
        positions[i] = glm::vec3(aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z);
        normals[i] = glm::vec3(aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z);
        if (aMesh->mTextureCoords[0])
        {
            uv[i] = glm::vec2(aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y);

        }
        if (aMesh->mTangents)
        {
            tangents[i] = glm::vec3(aMesh->mTangents[i].x, aMesh->mTangents[i].y, aMesh->mTangents[i].z);
            bitangents[i] = glm::vec3(aMesh->mBitangents[i].x, aMesh->mBitangents[i].y, aMesh->mBitangents[i].z);
        }
        if (positions[i].x < pMin.x) pMin.x = positions[i].x;
        if (positions[i].y < pMin.y) pMin.y = positions[i].y;
        if (positions[i].z < pMin.z) pMin.z = positions[i].z;
        if (positions[i].x > pMax.x) pMax.x = positions[i].x;
        if (positions[i].y > pMax.y) pMax.y = positions[i].y;
        if (positions[i].z > pMax.z) pMax.z = positions[i].z;
    }
    for (unsigned int f = 0; f < aMesh->mNumFaces; ++f)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            indices[f * 3 + i] = aMesh->mFaces[f].mIndices[i];
        }
    }

    Mesh* mesh = new Mesh;
    mesh->m_vecPos = positions;
    mesh->m_vecUV = uv;
    mesh->m_vecNormal = normals;
    mesh->m_vecTangent = tangents;
    mesh->m_vecBitangent = bitangents;
    mesh->m_vecIndices = indices;
    mesh->m_topology = TRIANGLES;
    mesh->Finalize(true);

    out_Min.x = pMin.x;
    out_Min.y = pMin.y;
    out_Min.z = pMin.z;
    out_Max.x = pMax.x;
    out_Max.y = pMax.y;
    out_Max.z = pMax.z;

    MeshLoader::meshStore.push_back(mesh);

    return mesh;
}
// --------------------------------------------------------------------------------------------
Material* MeshLoader::parseMaterial(aiMaterial* aMaterial, const aiScene* aScene, std::string directory)
{
    Material* material;

    aiString file;
    aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
    std::string diffPath = std::string(file.C_Str());
    bool alpha = false;
    if (diffPath.find("_alpha") != std::string::npos)
    {
        ResourceManager::getInstance()->LoadShader("alpha discard", "", "");
        material = ResourceManager::getInstance()->CreateMaterial("alpha discard");
        alpha = true;
    }
    else
    {
        material = ResourceManager::getInstance()->CreateMaterial("default");
    }

    if (aMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString file;
        aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
        std::string fileName = MeshLoader::processPath(&file, directory);

        Texture* texture = ResourceManager::getInstance()->LoadTexture(fileName, fileName, GL_TEXTURE_2D, alpha ? GL_RGBA : GL_RGB, true);
        if (texture)
        {
            material->SetTexture(TexAlbedo, texture, 3);
        }
    }
    if (aMaterial->GetTextureCount(aiTextureType_DISPLACEMENT) > 0)
    {
        aiString file;
        aMaterial->GetTexture(aiTextureType_DISPLACEMENT, 0, &file);
        std::string fileName = MeshLoader::processPath(&file, directory);

        Texture* texture = ResourceManager::getInstance()->LoadTexture(fileName, fileName);
        if (texture)
        {
            material->SetTexture(TexNormal, texture, 4);
        }
    }
    if (aMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
    {
        aiString file;
        aMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
        std::string fileName = MeshLoader::processPath(&file, directory);

        Texture* texture = ResourceManager::getInstance()->LoadTexture(fileName, fileName);
        if (texture)
        {
            material->SetTexture(TexMetallic, texture, 5);
        }
    }
    if (aMaterial->GetTextureCount(aiTextureType_SHININESS) > 0)
    {
        aiString file;
        aMaterial->GetTexture(aiTextureType_SHININESS, 0, &file);
        std::string fileName = MeshLoader::processPath(&file, directory);

        Texture* texture = ResourceManager::getInstance()->LoadTexture(fileName, fileName);
        if (texture)
        {
            material->SetTexture(TexRoughness, texture, 6);
        }
    }
    if (aMaterial->GetTextureCount(aiTextureType_AMBIENT) > 0)
    {
        aiString file;
        aMaterial->GetTexture(aiTextureType_AMBIENT, 0, &file);
        std::string fileName = MeshLoader::processPath(&file, directory);

        Texture* texture = ResourceManager::getInstance()->LoadTexture(fileName, fileName);
        if (texture)
        {
            material->SetTexture(TexAO, texture, 7);
        }
    }

    return material;
}

std::string MeshLoader::processPath(aiString* aPath, std::string directory)
{
    std::string path = std::string(aPath->C_Str());
    int count = directory.rfind("\\");
    if (path.find(":/") == std::string::npos || path.find(":\\") == std::string::npos)
        path = directory.substr(0, count) + "\\" + path;
    return path;
}
