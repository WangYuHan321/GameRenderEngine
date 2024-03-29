#include "AssimpParser.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include "../../Animation/Animation.h"
#include "../../Render/Animation/Bone.h"

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

bool AssimpParser::LoadAnim(const std::string& p_fileName, std::vector<Animation*>& p_anim, EModelParserFlags p_flags)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(p_fileName, static_cast<unsigned int>(p_flags));

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        return false;

    if (scene && scene->mRootNode)
    {
        for (unsigned int i = 0; i < scene->mNumAnimations; i++)
        {
            auto animation = scene->mAnimations[i];
            Animation* pAnim = new Animation();
            InitAnim(animation, scene, pAnim, p_fileName.c_str());
            p_anim.push_back(pAnim);
        }
    }
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
		p_meshes.push_back( ProcessMesh(&nodeTransformation, mesh, p_scene,mesh->mMaterialIndex) ); // The model will handle mesh destruction
	}

	// Then do the same for each of its children
	for (uint32_t i = 0; i < p_node->mNumChildren; ++i)
	{
		ProcessNode(&nodeTransformation, p_node->mChildren[i], p_scene, p_meshes);
	}
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


void AssimpParser::InitAnim(aiAnimation* aiAnimation, const struct aiScene* p_scene, Animation* anim, const char* fileName)
{
    using fs = std::filesystem::path;
    anim->animType = AnimType::Assimp;
    fs path = fs(fileName);
    anim->path = fileName;
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
