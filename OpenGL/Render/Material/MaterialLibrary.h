#pragma once
#include"../Shader/EShader.h"
#include"../../Util/Singleton.h"

class Renderer;
class Material;

class MaterialLibrary
{
private:
	//默认 最基础的Material ID
	std::map<uint32, Material*> m_DefaultMaterials;
	// Material 游戏运行的Material
	std::vector<Material*> m_Materials;

public:

	MaterialLibrary();
	~MaterialLibrary();

	CShader* dirShader;
	Material* defaultBlitMaterial;

	CShader* deferredAmbientShader;
	CShader* deferredIrradianceShader;
	CShader* deferredDirectionalShader;
	CShader* deferredPointShader;

	CShader* dirShadowShader;

	Material* debugLightMaterial;

	Material* GetDefaultBlitMaterial();
	Material* CreateMaterial(std::string base);
	Material* CreateCustomMaterial(CShader* shader);
};

