#pragma once

#include <string>
#include <vector>
#include <GLM/glm.hpp>
#include "../../Util/Singleton.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
struct aiString;

class SceneNode;
class Mesh;
class Material;

class MeshLoader : public CSingleton<MeshLoader>
{
private:

    std::vector<Mesh*> meshStore;
public:
    void       Clean();
    SceneNode* LoadMesh(std::string path, bool setDefaultMaterial = true);
private:
    SceneNode* processNode(aiNode* aNode, const aiScene* aScene, std::string directory, bool setDefaultMaterial);
    Mesh* parseMesh(aiMesh* aMesh, const aiScene* aScene, glm::vec3& out_Min, glm::vec3& out_Max);
    Material* parseMaterial(aiMaterial* aMaterial, const aiScene* aScene, std::string directory);

    std::string processPath(aiString* path, std::string directory);
};
