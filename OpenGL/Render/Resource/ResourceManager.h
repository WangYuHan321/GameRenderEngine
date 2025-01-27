#pragma once
#include "../Shader/Texture.h"
#include "../Shader/TextureCube.h"
#include "../Shader/EShader.h"
#include "../../Scene/SceneNode.h"
#include "../../Util/common.h"

class Renderer;
class GlobalContext;

class ResourceManager :public CSingleton<ResourceManager>
{
private:
	std::map<uint32, CShader> m_shaders;
	std::map<uint32, Texture> m_textuers;
	std::map<uint32, TextureCube> m_texturesCube;
	std::map<uint32, SceneNode*> m_meshes;
	std::map<uint32, Material> m_material;
	
	std::map<uint32, Material> m_otherMaterial;
	uint32 m_otherNum = 0;

	std::string m_assetPath = "";

public:

	ResourceManager();
	~ResourceManager();

	Material* LoadMaterial(std::string name, CShader* p_shader = nullptr);
	CShader* LoadShader(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defines = std::vector<std::string>());
	Texture* LoadTexture(std::string name, std::string path, GLenum target = GL_TEXTURE_2D, GLenum format = GL_RGBA, bool srgb = false);
	Texture* LoadHDRTexture(std::string name, std::string path);
	SceneNode* LoadMesh(std::string name, std::string path);

	Material* CreateMaterial(std::string name);
	Material* CreateCustomMaterial(CShader* p_shader);

	string GetLocatPath(string path);
	void SetAssetPath(const string strPath) { m_assetPath = strPath; }

	void SetContext(GlobalContext* p_context) { m_context = p_context; }

	void OnStartUp();
	void OnEnd();

	void GenerateDefaultMaterials();
	void GenerateInternalMaterials();

private:
	GlobalContext* m_context=0;
};

