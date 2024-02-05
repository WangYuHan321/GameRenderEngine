#include "AssimpParser.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>


bool AssimpParser::LoadModel(const std::string& p_fileName, std::vector<Mesh*>& p_meshes, std::vector<std::string>& p_materials, EModelParserFlags p_parserFlags)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(p_fileName, static_cast<unsigned int>(p_parserFlags));

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		return false;

	ProcessMaterials(scene, p_materials);

	aiMatrix4x4 identity;

	ProcessNode(&identity, scene->mRootNode, scene, p_meshes);

	return true;
}

void AssimpParser::ProcessMaterials(const aiScene* p_scene, std::vector<std::string>& p_materials)
{
	for (uint32_t i = 0; i < p_scene->mNumMaterials; ++i)
	{
		aiMaterial* material = p_scene->mMaterials[i];
		if (material)
		{
			aiString name;
			aiGetMaterialString(material, AI_MATKEY_NAME, &name);//获取材质原先的名字
			p_materials.push_back(name.C_Str());
		}
	}
}

void AssimpParser::ProcessNode(void* p_transform, aiNode* p_node, const aiScene* p_scene, std::vector<Mesh*>& p_meshes)
{
	aiMatrix4x4 nodeTransformation = *reinterpret_cast<aiMatrix4x4*>(p_transform) * p_node->mTransformation;

	// Process all the node's meshes (if any)
	for (uint32_t i = 0; i < p_node->mNumMeshes; ++i)
	{
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
		;
		p_meshes.push_back( ProcessMesh(mesh, p_scene,mesh->mMaterialIndex) ); // The model will handle mesh destruction
	}

	// Then do the same for each of its children
	for (uint32_t i = 0; i < p_node->mNumChildren; ++i)
	{
		ProcessNode(&nodeTransformation, p_node->mChildren[i], p_scene, p_meshes);
	}
}

Mesh* AssimpParser::ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene, uint32 p_materalIndex)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    std::vector<unsigned int> indices;

    positions.resize(p_mesh->mNumVertices);
    normals.resize(p_mesh->mNumVertices);
    if (p_mesh->mNumUVComponents[0] > 0)
    {
        uv.resize(p_mesh->mNumVertices);
        tangents.resize(p_mesh->mNumVertices);
        bitangents.resize(p_mesh->mNumVertices);
    }

    indices.resize(p_mesh->mNumFaces * 3);


    for (unsigned int i = 0; i < p_mesh->mNumVertices; ++i)
    {
        positions[i] = glm::vec3(p_mesh->mVertices[i].x, p_mesh->mVertices[i].y, p_mesh->mVertices[i].z);
        normals[i] = glm::vec3(p_mesh->mNormals[i].x, p_mesh->mNormals[i].y, p_mesh->mNormals[i].z);
        if (p_mesh->mTextureCoords[0])
        {
            uv[i] = glm::vec2(p_mesh->mTextureCoords[0][i].x, p_mesh->mTextureCoords[0][i].y);

        }
        if (p_mesh->mTangents)
        {
            tangents[i] = glm::vec3(p_mesh->mTangents[i].x, p_mesh->mTangents[i].y, p_mesh->mTangents[i].z);
            bitangents[i] = glm::vec3(p_mesh->mBitangents[i].x, p_mesh->mBitangents[i].y, p_mesh->mBitangents[i].z);
        }
    }
    for (unsigned int f = 0; f < p_mesh->mNumFaces; ++f)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            indices[f * 3 + i] = p_mesh->mFaces[f].mIndices[i];
        }
    }

    Mesh* mesh = new Mesh;
    mesh->Positions = positions;
    mesh->UV = uv;
    mesh->Normals = normals;
    mesh->Tangents = tangents;
    mesh->Bitangents = bitangents;
    mesh->Indices = indices;
    mesh->Topology = TRIANGLES;
    mesh->MaterialIndex = p_materalIndex;

    mesh->Finalize(true);

    return mesh;
}
