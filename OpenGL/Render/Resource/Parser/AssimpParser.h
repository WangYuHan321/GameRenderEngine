#pragma once

#include "IModelParser.h"
#include "../../Mesh/Mesh.h"
struct aiMesh;

class AssimpParser : public IModelParser
{
public:
	virtual bool LoadModel(const std::string& p_fileName, std::vector<Mesh*>& p_meeshes,
		std::vector<std::string>& p_materials, EModelParserFlags p_flags) override;

private:

	void ProcessMaterials(const struct aiScene* p_scene, std::vector<std::string>& p_materials);;
	void ProcessNode(void* p_transform, struct aiNode* p_node, const struct aiScene* p_scene, std::vector<Mesh*>& p_meshes);
	Mesh* ProcessMesh(aiMesh* aMesh, const aiScene* aScene, uint32 p_materalIndex);
};

