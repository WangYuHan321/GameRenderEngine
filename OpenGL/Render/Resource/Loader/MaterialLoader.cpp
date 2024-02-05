#include "MaterialLoader.h"

Material MaterialLoader::LoadMaterial(std::string name, CShader* p_shader)
{
	return p_shader == nullptr ? Material() : Material(p_shader);
}

Material MaterialLoader::LoadMaterial(CShader* p_shader)
{
	return Material(p_shader);
}



Material* MaterialLoader::Create(const std::string& p_path)
{
	return nullptr;
}

bool MaterialLoader::Destroy(Material*& p_material)
{
	return true;
}