#pragma once

#include <string>
#include "../../Mesh/Material.h"
#include "../../Util/Singleton.h"

class Material;
class CShader;

class MaterialLoader : public CSingleton<MaterialLoader>
{
public:
	
	Material LoadMaterial(std::string name, CShader* p_shader = nullptr);
	Material LoadMaterial(CShader* p_shader);

	void Save(Material& p_material, std::string p_path);

	Material* Create(const std::string& p_path);
	bool Destroy(Material*& p_material);

};

