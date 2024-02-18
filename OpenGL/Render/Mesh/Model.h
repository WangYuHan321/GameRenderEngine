#if 0 

#pragma once
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include"../../Util/common.h"
#include"Mesh.h"

class EShader;
class AABB;

#define DIFFUSE_TEX "u_DiffuseTexture"
#define SPECULAR_TEX "u_SpecularTexture"
#define NORMAL_TEX "u_NormalTexture"
#define ROUGHNESS_TEX "u_RoughnessTexture"
#define METALLIC_TEX "u_MetallicTexture"

class Model
{
public:
	Model(const string& modelPath);

	void init(const EShader& shader);
	void update(const EShader& shader);
	Mesh processMesh(const aiMesh* mesh);
	void processVertex(const aiMesh* mesh, std::vector<MeshVertex>& v);
	void processMeshTexture(const aiMesh* mesh, std::vector<MeshTexture>& m);
	void processMeshIndices(const aiMesh* mesh, std::vector<GLint>& i);
	void processMeshMat(const aiMesh* mesh, MeshMatProperty& mat);
	void LoadTextureFromMaterial(aiTextureType v, const aiMaterial* m, const string& tab, std::vector<MeshTexture>& vt);

private:
	GLint m_meshCount = -1;
	const aiScene* m_pScene;

	std::vector<Mesh> m_Meshes;
	std::vector<MeshTexture> m_loadedTextures;


};

#endif

#pragma once

#include <vector>
#include <functional>
#include <GLM/glm.hpp>
#include <vector>
#include "../Bounding/BoundingSphere.h"

class Mesh;
class Material;
class BoundingSphere;


class Model
{
public:
	std::vector<Mesh*> m_meshes;
	std::vector<std::string> m_materialNames;
private:
	BoundingSphere m_boundingSphere;

public:

	Model();
	Model(std::vector<Mesh*>& p_mesh, std::vector<std::string>& p_material);
	~Model();

	const BoundingSphere& GetBoundingSphere() const;

public:
	void ComputeBoundingSphere();
};