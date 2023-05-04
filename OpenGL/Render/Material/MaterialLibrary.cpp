#include "MaterialLibrary.h"

#include "../Renderer.h"
#include "../Mesh/Mesh_ID.h"
#include "../Mesh/Material.h"
#include "../../Util/common.h"
#include"../Resource/ResourceManager.h"

MaterialLibrary::MaterialLibrary()
{
	m_DefaultMaterials[SID("default")] = ResourceManager::getInstance()->LoadMaterial("default");
	//m_DefaultMaterials[SID("glass")] = ResourceManager::getInstance()->LoadMaterial("glass");
	//m_DefaultMaterials[SID("alpha blend")] = ResourceManager::getInstance()->LoadMaterial("alpha blend");
	m_DefaultMaterials[SID("alpha discard")] = ResourceManager::getInstance()->LoadMaterial("alpha discard");
	defaultBlitMaterial = ResourceManager::getInstance()->LoadMaterial("blit");
	debugLightMaterial = ResourceManager::getInstance()->LoadMaterial("debug light");
	dirShadowShader = ResourceManager::getInstance()->LoadShader("shadow direction",
		"Shader\\shadow_cast.vs", "Shader\\shadow_cast.fs");
}

MaterialLibrary::~MaterialLibrary()
{
}


Material* MaterialLibrary::GetDefaultBlitMaterial()
{
	return defaultBlitMaterial;
}

Material* MaterialLibrary::CreateMaterial(std::string base)
{
	auto found = m_DefaultMaterials.find(SID(base));
	if(found != m_DefaultMaterials.end())
	{
		return ResourceManager::getInstance()->CreateMaterial(base);
	}
	else
	{
		Log("Material is error!!!\n");
		return nullptr;
	}
}

Material* MaterialLibrary::CreateCustomMaterial(CShader* shader)
{
	return ResourceManager::getInstance()->CreateCustomMaterial(shader);
}



