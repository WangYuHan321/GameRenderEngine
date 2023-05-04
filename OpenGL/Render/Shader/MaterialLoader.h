#pragma once

#include <string>
#include "../Mesh/Material.h"
#include "../../Util/Singleton.h"

class Material;
class CShader;

class MaterialLoader : public CSingleton<MaterialLoader>
{
public:
	
	Material LoadMaterial(std::string name, CShader* p_shader = nullptr);
	Material LoadMaterial(CShader* p_shader);

};

