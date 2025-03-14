#pragma once

#include "IModelParser.h"
#include "IAnimationParser.h"
#include "../../Mesh/Mesh.h"
#include "../../Mesh/Model.h"
struct aiMesh;

class AssimpParser : public IModelParser, public IAnimParser
{
public:
	virtual bool LoadModel(const std::string& p_fileName, std::vector<Mesh*>& p_meeshes,
		std::vector<std::string>& p_materials, EModelParserFlags p_flags) override;
	
	bool LoadModelEx(const std::string& p_fileName, Model& p_model, EModelParserFlags p_flags);
	void ProcessNodeEx(void* p_transform, struct aiNode* p_node, const struct aiScene* p_scene, Model& p_model);
	Mesh* ProcessMeshEx(void* p_transform, Model& p_model, aiMesh* aMesh, const aiScene* aScene, uint32 p_materalIndex);

	virtual bool LoadAnim(const std::string& p_fileName, std::vector<Animation*>& p_anim, EModelParserFlags p_flags) override;

	bool LoadNewModel(const std::string& p_fileName, std::vector<Mesh*>& p_meeshes,
		std::vector<std::string>& p_materials, EModelParserFlags p_flags);
private:

	void ProcessMaterials(const struct aiScene* p_scene, std::vector<std::string>& p_materials);;
	void ExtraMaterialTexture(const aiScene* p_Scene, aiMesh* p_Mesh, Mesh& other);
	void ExtraMeshBoneInfo(std::vector<Vertex>& vertices, aiMesh* p_Mesh, Model& p_model);
	void ProcessNode(void* p_transform, struct aiNode* p_node, const struct aiScene* p_scene, std::vector<Mesh*>& p_meshes);
	Mesh* ProcessMesh(void* p_transform, aiMesh* aMesh, const aiScene* aScene, uint32 p_materalIndex);
	Mesh* ProcessNewMesh(void* p_transform, aiMesh* aMesh, const aiScene* aScene, uint32 p_materalIndex);
	void ProcessNewNode(void* p_transform, struct aiNode* p_node, const struct aiScene* p_scene, std::vector<Mesh*>& p_meshes);

	void InitAnim(aiAnimation* p_aiAnimation, const struct aiScene* p_scene,  Animation* p_anim);
	void ProcessBone(const aiAnimation* animation, Animation* anim, const aiNode* root_node);
	void ProcessBindPose(Animation* anim, const aiNode* node);

	void SetCurDirectory(std::string path);

private:
	std::string curLoadDir = "";

};

