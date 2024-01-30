#include"ResourceManager.h"

#include "../Shader/TextureLoader.h"
#include "../Shader/ShaderLoader.h"
#include "../Shader/MeshLoader.h"
#include "../Shader/MaterialLoader.h"
#include "../Mesh/Mesh_ID.h"

#include "../../Scene/Scene.h"
#include "../../Scene/SceneManager.h"
#include"../../Util/Utils.h"

#include "../../Global/GlobalContext.h"

string ResourceManager::GetLocatPath(string path)
{
	bool isAddPath = (path.find(m_assetPath) != 0);
	path = isAddPath ? m_assetPath + path : path;
	return path;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto item : m_meshes)
		delete item.second;
}

Material* ResourceManager::LoadMaterial(std::string name, CShader* p_shader)
{
	uint32 id = SID(name);

	if (m_material.find(id) != m_material.end())
	{
		return &m_material[id];
	}
	
	Material material = MaterialLoader::getInstance()->LoadMaterial(name, p_shader);
	m_material[id] = material;
	return &m_material[id];

}

CShader* ResourceManager::LoadShader(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defines)
{
	uint32 id = SID(name);

	if (m_shaders.find(id) != m_shaders.end())
	{
		return &m_shaders[id];
	}
	vsPath = GetLocatPath(vsPath);
	fsPath = GetLocatPath(fsPath);

	CShader shader = ShaderLoader::getInstance()->Load(name, vsPath, fsPath, defines);
	
	m_shaders[id] = shader;
	return &m_shaders[id];
}

Texture* ResourceManager::LoadTexture(std::string name, std::string path, GLenum target, GLenum format, bool srgb)
{
	LOG_INFO(name + "\n");
	unsigned int id = SID(name);
	if (m_textuers.find(id) != ResourceManager::m_textuers.end())
	{
		return &m_textuers[id];
	}
	path = GetLocatPath(path);

	Texture texture = TextureLoader::getInstance()->LoadTexture(path, target, format, srgb);

	if (texture.Width > 0)
	{
		ResourceManager::m_textuers[id] = texture;
		return &ResourceManager::m_textuers[id];
	}
	else
	{
		LOG_ERROR("加载纹理失败！！！\n");
		return nullptr;
	}

}

Texture* ResourceManager::LoadHDRTexture(std::string name, std::string path)
{
	uint32 id = SID(name);
	if (m_textuers.find(id) != m_textuers.end())
		return &m_textuers[id];
	path = GetLocatPath(path);

	Texture texture = TextureLoader::getInstance()->LoadHDRTexture(path);
	if (texture.Width > 0)
	{
		m_textuers[id] = texture;
		return &m_textuers[id];
	}
	else
	{
		return nullptr;
	}

}

SceneNode* ResourceManager::LoadMesh(std::string name, std::string path)
{
	unsigned int id = SID(name);
	if (m_meshes.find(id) != m_meshes.end())
	{
		return m_context->m_sceneMgr->GetActiveScene()->MakeSceneNode(m_meshes[id]);
	}
	path = GetLocatPath(path);

	SceneNode* node = MeshLoader::getInstance()->LoadMesh(path);
	m_meshes[id] = node;

	return m_context->m_sceneMgr->GetActiveScene()->MakeSceneNode(node);
}

Material* ResourceManager::CreateMaterial(std::string name)
{
	static uint64 number = 0;
	
	if (m_material.find(SID(name)) != m_material.end())
	{
		m_otherMaterial[m_otherNum] = m_material[SID(name)].Copy();
		return &m_otherMaterial[m_otherNum++];
	}
	return nullptr;
}

Material* ResourceManager::CreateCustomMaterial(CShader* p_shader)
{
	Material mat = MaterialLoader::getInstance()->LoadMaterial(p_shader);
	m_otherMaterial[m_otherNum] = mat;
	return &m_otherMaterial[m_otherNum++];
}

void ResourceManager::OnStartUp()
{
	GenerateDefaultMaterials();
	GenerateInternalMaterials();
}

void ResourceManager::OnEnd()
{

}

void ResourceManager::GenerateDefaultMaterials()
{
	CShader* defaultShader = LoadShader("default","Shader\\deferred\\g_buffer.vs", "Shader\\deferred\\g_buffer.fs");
	Material* defaultMaterial = LoadMaterial("default", defaultShader);
	defaultMaterial->Type = MATERIAL_DEFAULT;

	//默认shader 中 默认纹理 3 4 5 6
	defaultMaterial->SetTexture(TexAlbedo, LoadTexture("default albedo", "Asset\\texture\\checkerboard.png", GL_TEXTURE_2D, GL_RGB), 3);
	defaultMaterial->SetTexture(TexNormal, LoadTexture("default normal", "Asset\\texture\\norm.png"), 4);
	defaultMaterial->SetTexture(TexMetallic, LoadTexture("default metallic", "Asset\\texture\\black.png"), 5);
	defaultMaterial->SetTexture(TexRoughness, LoadTexture("default wroughness", "Asset\\texture\\checkerboard.png"), 6);

	//glass材质
	CShader* glassShader = LoadShader("glass", "Shader\\forward_render.vs", "Shader\\forward_render.fs", { "ALPHA_BLEND" });
	glassShader->SetInt("lightShadowMap1", 10);
	glassShader->SetInt("lightShadowMap2", 10);
	glassShader->SetInt("lightShadowMap3", 10);
	glassShader->SetInt("lightShadowMap4", 10);
	Material* glassMat = LoadMaterial("glass", glassShader);
	glassMat->Type = MATERIAL_CUSTOM;
	glassMat->SetTexture(TexAlbedo, LoadTexture("glass albedo", "Asset\\texture\\glass.png", GL_TEXTURE_2D, GL_RGBA), 0);
	glassMat->SetTexture(TexNormal, LoadTexture("glass normal", "Asset\\texture\\pbr\\plastic\\normal.png"), 1);
	glassMat->SetTexture(TexMetallic, LoadTexture("glass metallic", "Asset\\texture\\pbr/plastic\\metallic.png"), 2);
	glassMat->SetTexture(TexRoughness, LoadTexture("glass roughness", "Asset\\texture\\pbr\\plastic\\roughness.png"), 3);
	glassMat->SetTexture(TexAO, LoadTexture("glass ao", "Asset\\texture\\pbr\\plastic\\ao.png"), 4);
	glassMat->Blend = true;

	// alpha blend material
	CShader* alphaBlendShader = LoadShader("alpha blend", "Shader\\forward_render.vs","Shader\\forward_render.fs", 
		{ "ALPHA_BLEND" });
	alphaBlendShader->activeShader();
	alphaBlendShader->SetInt("lightShadowMap1", 10);
	alphaBlendShader->SetInt("lightShadowMap2", 10);
	alphaBlendShader->SetInt("lightShadowMap3", 10);
	alphaBlendShader->SetInt("lightShadowMap4", 10);
	Material* alphaBlendMaterial = LoadMaterial("alpha blend", alphaBlendShader);
	alphaBlendMaterial->Type = MATERIAL_CUSTOM;
	alphaBlendMaterial->Blend = true;

	// alpha cutout material
	CShader* alphaDiscardShader = LoadShader("alpha discard","Shader\\forward_render.vs", "Shader\\forward_render.fs",
		{ "ALPHA_DISCARD" });
	alphaDiscardShader->activeShader();
	alphaDiscardShader->SetInt("lightShadowMap1", 10);
	alphaDiscardShader->SetInt("lightShadowMap2", 10);
	alphaDiscardShader->SetInt("lightShadowMap3", 10);
	alphaDiscardShader->SetInt("lightShadowMap4", 10);
	Material* alphaDiscardMaterial = LoadMaterial("alpha discard", alphaDiscardShader);
	alphaDiscardMaterial->Type = MATERIAL_CUSTOM;
	alphaDiscardMaterial->Cull = false;
}

void ResourceManager::GenerateInternalMaterials()
{
	CShader* defaultBlitShader = LoadShader("blit", "Shader\\scene\\screen_quad.vs", "Shader\\scene\\screen_quad.fs");
	LoadMaterial("blit", defaultBlitShader);

	//deferred shader
	// 环境光       根据BRDF来计算光照信息
	// 辐照度
	// 方向光
	// 点光源
	CShader* deferredAmbientShader = LoadShader("deferred ambient",
		"Shader\\screen_ambient.vs", "Shader\\ambient.fs");
	deferredAmbientShader->activeShader();
	deferredAmbientShader->SetInt("gPositionMetallic", 0);
	deferredAmbientShader->SetInt("gNormalRoughness", 1);
	deferredAmbientShader->SetInt("gAlbedoAO", 2);
	deferredAmbientShader->SetInt("envIrradiance", 3);
	deferredAmbientShader->SetInt("envPrefilter", 4);
	deferredAmbientShader->SetInt("BRDFLUT", 5);
	deferredAmbientShader->SetInt("TexSSAO", 6);

	CShader* deferredIrradianceShader = LoadShader("deferred irradiance",
		"Shader\\deferred\\ambient_irradiance.vs", "Shader\\deferred\\ambient_irradiance.fs");
	deferredIrradianceShader->activeShader();
	deferredIrradianceShader->SetInt("gPositionwwMetallic", 0);
	deferredIrradianceShader->SetInt("gNormalRoughness", 1);
	deferredIrradianceShader->SetInt("gAlbedoAO", 2);
	deferredIrradianceShader->SetInt("envIrradiance", 3);
	deferredIrradianceShader->SetInt("envPrefilter", 4);
	deferredIrradianceShader->SetInt("BRDFLUT", 5);
	deferredIrradianceShader->SetInt("TexSSAO", 6);

	CShader* deferredDirectionalShader = ResourceManager::getInstance()->LoadShader("deferred directional",
		"Shader\\deferred\\directional.vs", "Shader\\deferred\\directional.fs");
	deferredDirectionalShader->activeShader();
	deferredDirectionalShader->SetInt("gPositionMetallic", 0);
	deferredDirectionalShader->SetInt("gNormalRoughness", 1);
	deferredDirectionalShader->SetInt("gAlbedoAO", 2);
	deferredDirectionalShader->SetInt("lightShadowMap", 3);

	CShader* deferredPointShader = LoadShader("deferred pointLight",
		"Shader\\deferred/point_light.vs", "Shader\\deferred\\point_light.fs");
	deferredPointShader->activeShader();
	deferredPointShader->SetInt("gPositionMetallic", 0);
	deferredPointShader->SetInt("gNormalRoughness", 1);
	deferredPointShader->SetInt("gAlbedoAO", 2);

	CShader* dirShadowShader = LoadShader("shadow direction",
		"Shader\\shadow_cast.vs", "Shader\\shadow_cast.fs");

	CShader* debugLightShader = LoadShader("debug light", "Shader\\light.vs", "Shader\\light.fs");
	LoadMaterial("debug light", debugLightShader);
}