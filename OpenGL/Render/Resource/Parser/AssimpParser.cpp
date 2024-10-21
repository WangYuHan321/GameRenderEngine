#include "AssimpParser.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include "../../Animation/Animation.h"
#include "../../Render/Animation/Bone.h"
#include "../../Resource/Loader/TextureLoader.h"
#include "../../Resource/Loader/MaterialLoader.h"

bool AssimpParser::LoadModel(const std::string& p_fileName, std::vector<Mesh*>& p_meshes, std::vector<std::string>& p_materials, EModelParserFlags p_parserFlags)
{
	Assimp::Importer import;
    SetCurDirectory(p_fileName);
	const aiScene* scene = import.ReadFile(p_fileName, static_cast<unsigned int>(p_parserFlags));

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		return false;

	ProcessMaterials(scene, p_materials);

	aiMatrix4x4 identity;

	ProcessNode(&identity, scene->mRootNode, scene, p_meshes);

	return true;
}

bool AssimpParser::LoadAnim(const std::string& p_fileName, std::vector<Animation*>& p_anim, EModelParserFlags p_flags)
{
    Assimp::Importer import;
    SetCurDirectory(p_fileName);
    const aiScene* scene = import.ReadFile(p_fileName, static_cast<unsigned int>(p_flags));

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        return false;

    if (scene && scene->mRootNode)
    {
        for (unsigned int i = 0; i < scene->mNumAnimations; i++)
        {
            auto animation = scene->mAnimations[i];
            Animation* pAnim = new Animation();
            pAnim->path = p_fileName;
            InitAnim(animation, scene, pAnim);

            p_anim.push_back(pAnim);
        }
    }
}

bool AssimpParser::LoadNewModel(const std::string& p_fileName, std::vector<Mesh*>& p_meshes, std::vector<std::string>& p_materials, EModelParserFlags p_parserFlags)
{
    Assimp::Importer import;
    SetCurDirectory(p_fileName);
    const aiScene* scene = import.ReadFile(p_fileName, static_cast<unsigned int>(p_parserFlags));

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        return false;

    ProcessMaterials(scene, p_materials);

    aiMatrix4x4 identity;

    ProcessNewNode(&identity, scene->mRootNode, scene, p_meshes);

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

void AssimpParser::ExtraMaterialTexture(const aiScene* p_Scene, aiMesh* p_Mesh, Mesh& other)
{
    aiMaterial* pMaterial = p_Scene->mMaterials[p_Mesh->mMaterialIndex];
    MaterialProperties mat_properties;
    aiColor3D color{};

    pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
    mat_properties.Ambient.r = color.r;
    mat_properties.Ambient.g = color.g;
    mat_properties.Ambient.b = color.b;

    pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    mat_properties.Diffuse.r = color.r;
    mat_properties.Diffuse.g = color.g;
    mat_properties.Diffuse.b = color.b;

    pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
    mat_properties.Specular.r = color.r;
    mat_properties.Specular.g = color.g;
    mat_properties.Specular.b = color.b;

    float shininess{};
    pMaterial->Get(AI_MATKEY_SHININESS, shininess);
    mat_properties.Shininess = shininess;

    other.m_materialProperty = mat_properties;

    for (int i = 0; i < pMaterial->GetTextureCount(aiTextureType_DIFFUSE); i++)
    {
        aiString str;
        pMaterial->GetTexture(aiTextureType_DIFFUSE, i, &str);
        other.m_vecTextures["diffuse_" + std::to_string(i)] = TextureLoader::getInstance()->LoadTexture(curLoadDir + "/" + str.C_Str(), GL_TEXTURE_2D, GL_RGBA);
    }

    for (int i = 0; i < pMaterial->GetTextureCount(aiTextureType_SPECULAR); i++)
    {
        aiString str;
        pMaterial->GetTexture(aiTextureType_SPECULAR, i, &str);
        other.m_vecTextures["specular_" + std::to_string(i)] = TextureLoader::getInstance()->LoadTexture(curLoadDir + "/" + str.C_Str(), GL_TEXTURE_2D, GL_RGBA);
    }

    for (int i = 0; i < pMaterial->GetTextureCount(aiTextureType_NORMALS); i++)
    {
        aiString str;
        pMaterial->GetTexture(aiTextureType_NORMALS, i, &str);
        other.m_vecTextures["normal_" + std::to_string(i)] = TextureLoader::getInstance()->LoadTexture(curLoadDir + "/" + str.C_Str(), GL_TEXTURE_2D, GL_RGBA);
    }

    for (int i = 0; i < pMaterial->GetTextureCount(aiTextureType_AMBIENT); i++)
    {
        aiString str;
        pMaterial->GetTexture(aiTextureType_AMBIENT, i, &str);
        other.m_vecTextures["ambient_" + std::to_string(i)] = TextureLoader::getInstance()->LoadTexture(curLoadDir + "/" + str.C_Str(), GL_TEXTURE_2D, GL_RGBA);
    }

    for (int i = 0; i < pMaterial->GetTextureCount(aiTextureType_HEIGHT); i++)
    {
        aiString str;
        pMaterial->GetTexture(aiTextureType_HEIGHT, i, &str);
        other.m_vecTextures["height_" + std::to_string(i)] = TextureLoader::getInstance()->LoadTexture(curLoadDir + "/" + str.C_Str(), GL_TEXTURE_2D, GL_RGBA);
    }
}

void AssimpParser::ProcessNode(void* p_transform, aiNode* p_node, const aiScene* p_scene, std::vector<Mesh*>& p_meshes)
{
	aiMatrix4x4 nodeTransformation = *reinterpret_cast<aiMatrix4x4*>(p_transform) * p_node->mTransformation;

	// Process all the node's meshes (if any)
	for (uint32_t i = 0; i < p_node->mNumMeshes; ++i)
	{
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
		p_meshes.push_back( ProcessMesh(&nodeTransformation, mesh, p_scene,mesh->mMaterialIndex) ); // The model will handle mesh destruction
	}

	// Then do the same for each of its children
	for (uint32_t i = 0; i < p_node->mNumChildren; ++i)
	{
		ProcessNode(&nodeTransformation, p_node->mChildren[i], p_scene, p_meshes);
	}
}

void AssimpParser::ProcessNewNode(void* p_transform, aiNode* p_node, const aiScene* p_scene, std::vector<Mesh*>& p_meshes)
{
    aiMatrix4x4 nodeTransformation = *reinterpret_cast<aiMatrix4x4*>(p_transform) * p_node->mTransformation;

    // Process all the node's meshes (if any)
    for (uint32_t i = 0; i < p_node->mNumMeshes; ++i)
    {
        aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
        p_meshes.push_back(ProcessNewMesh(&nodeTransformation, mesh, p_scene, mesh->mMaterialIndex)); // The model will handle mesh destruction
    }

    // Then do the same for each of its children
    for (uint32_t i = 0; i < p_node->mNumChildren; ++i)
    {
        ProcessNode(&nodeTransformation, p_node->mChildren[i], p_scene, p_meshes);
    }
}

Mesh* AssimpParser::ProcessNewMesh(void* p_transform, aiMesh* p_mesh, const aiScene* aScene, uint32 p_materalIndex)
{
    aiMatrix4x4 meshTransformation = *reinterpret_cast<aiMatrix4x4*>(p_transform);

    std::vector<Vertex> vertexs;
    std::vector<unsigned int> indices;

    vertexs.resize(p_mesh->mNumVertices);
    indices.resize(p_mesh->mNumFaces * 3);


    for (unsigned int i = 0; i < p_mesh->mNumVertices; ++i)
    {
        aiVector3D _position = meshTransformation * p_mesh->mVertices[i];
        aiVector3D _normal = meshTransformation * (p_mesh->mNormals ? p_mesh->mNormals[i] : aiVector3D(0.0f, 0.0f, 0.0f));
        aiVector3D _texCoords = p_mesh->mTextureCoords[0] ? p_mesh->mTextureCoords[0][i] : aiVector3D(0.0f, 0.0f, 0.0f);
        aiVector3D _tangent = p_mesh->mTangents ? meshTransformation * p_mesh->mTangents[i] : aiVector3D(0.0f, 0.0f, 0.0f);
        aiVector3D _bitangent = p_mesh->mBitangents ? meshTransformation * p_mesh->mBitangents[i] : aiVector3D(0.0f, 0.0f, 0.0f);

        vertexs[i].Position = glm::vec3(_position.x, _position.y, _position.z);
        vertexs[i].Normal = glm::vec3(_normal.x, _normal.y, _normal.z);
        if (p_mesh->mTextureCoords[0])
        {
            vertexs[i].UV = glm::vec2(_texCoords.x, _texCoords.y);

        }
        if (p_mesh->mTangents)
        {
            vertexs[i].Tangent = glm::vec3(_tangent.x, _tangent.y, _tangent.z);
            vertexs[i].Bitangent = glm::vec3(_bitangent.x, _bitangent.y, _bitangent.z);
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
    mesh->m_vecVertex = vertexs;
    mesh->m_vecIndices = indices;
    mesh->m_topology = TRIANGLES;
    mesh->m_materialIndex = p_materalIndex;
    mesh->m_strName = p_mesh->mName.C_Str();

    ExtraMaterialTexture(aScene, p_mesh, *mesh);

    mesh->NewFinalize(true);

    return mesh;
}

Mesh* AssimpParser::ProcessMesh(void* p_transform, aiMesh* p_mesh, const aiScene* p_scene, uint32 p_materalIndex)
{
    aiMatrix4x4 meshTransformation = *reinterpret_cast<aiMatrix4x4*>(p_transform);

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
        aiVector3D _position = meshTransformation * p_mesh->mVertices[i];
        aiVector3D _normal = meshTransformation * (p_mesh->mNormals ? p_mesh->mNormals[i] : aiVector3D(0.0f, 0.0f, 0.0f));
        aiVector3D _texCoords = p_mesh->mTextureCoords[0] ? p_mesh->mTextureCoords[0][i] : aiVector3D(0.0f, 0.0f, 0.0f);
        aiVector3D _tangent = p_mesh->mTangents ? meshTransformation * p_mesh->mTangents[i] : aiVector3D(0.0f, 0.0f, 0.0f);
        aiVector3D _bitangent = p_mesh->mBitangents ? meshTransformation * p_mesh->mBitangents[i] : aiVector3D(0.0f, 0.0f, 0.0f);

        positions[i] = glm::vec3(_position.x, _position.y, _position.z);
        normals[i] = glm::vec3(_normal.x, _normal.y, _normal.z);
        if (p_mesh->mTextureCoords[0])
        {
            uv[i] = glm::vec2(_texCoords.x, _texCoords.y);

        }
        if (p_mesh->mTangents)
        {
            tangents[i] = glm::vec3(_tangent.x, _tangent.y, _tangent.z);
            bitangents[i] = glm::vec3(_bitangent.x, _bitangent.y, _bitangent.z);
        }
    }
    for (unsigned int f = 0; f < p_mesh->mNumFaces; ++f)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            indices[f * 3 + i] = p_mesh->mFaces[f].mIndices[i];
        }
    }

    Mesh* mesh = new Mesh(positions, uv, normals, tangents, bitangents, indices);

    mesh->SetName(p_mesh->mName.C_Str());
    mesh->SetMaterialIndex(p_materalIndex);
    mesh->SetTopology(TRIANGLES);

    ExtraMaterialTexture(p_scene, p_mesh, *mesh);

    mesh->Finalize(true);

    return mesh;
}


void AssimpParser::InitAnim(aiAnimation* aiAnimation, const struct aiScene* p_scene, Animation* anim)
{
    using fs = std::filesystem::path;
    anim->animType = AnimType::Assimp;
    fs path = fs(anim->path);
    anim->path = path.string();
    anim->name = path.filename().string();
    anim->duration = aiAnimation->mDuration;
    anim->fps = aiAnimation->mTicksPerSecond;
    ProcessBone(aiAnimation, anim,  p_scene->mRootNode);
    ProcessBindPose(anim, p_scene->mRootNode);
}

void AssimpParser::ProcessBone(const aiAnimation* animation, Animation* anim, const aiNode* root_node)
{
    int numSize = animation->mNumChannels;

    for (int i = 0; i < numSize; i++)
    {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.C_Str();

        const aiNode* node = root_node->FindNode(channel->mNodeName);
        if (node)
        {
            LOG_INFO(node->mParent->mName.C_Str());
            anim->nameBoneMap[boneName] = new Bone(boneName, channel, glm::inverse(AiMatToGlmMat(node->mTransformation)));
        }
    }
}

void AssimpParser::ProcessBindPose(Animation* anim, const aiNode* node)
{
    if (node)
    {
        std::string name(node->mName.C_Str());
        auto bindpose = AiMatToGlmMat(node->mTransformation);
        auto children_size = node->mNumChildren;
        anim->nameBindPoseMap[name] = bindpose;
        for (unsigned int i = 0; i < children_size; ++i)
        {
            ProcessBindPose(anim, node->mChildren[i]);
        }
    }
}

std::string ReplacePathSeparator(const std::string& path) {
    std::string result = path;
#ifdef _WIN32
    const char old_separator = '\\';
#else
    const char old_separator = '/';
#endif
    const char new_separator = '/';
    size_t start_pos = 0;
    while ((start_pos = result.find(old_separator, start_pos)) != std::string::npos) {
        result.replace(start_pos, 1, 1, new_separator);
        // 在替换后继续搜索，避免遗漏
        ++start_pos;
    }
    return result;
}

void AssimpParser::SetCurDirectory(std::string curPath)
{
    string directory = "";
    if (curPath.size() > 0)
    {
        string newStr = ReplacePathSeparator(curPath);

        if (int nPos = curPath.rfind("/"); nPos > 0)
        {
            directory = curPath.substr(0, nPos);
        }
    }
    curLoadDir = directory;
}
