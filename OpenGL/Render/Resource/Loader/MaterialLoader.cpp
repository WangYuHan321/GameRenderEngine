#include "MaterialLoader.h"
#include "ShaderLoader.h"
#include "../../Core/API/ISerializable.h"

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
	tinyxml2::TinyXMLDocument doc;
	doc.LoadFile(p_path.c_str());

	if (!doc.Error())
	{
		tinyxml2::XMLNode* root = doc.FirstChild();

		Material* pMaterial = new Material();
#ifdef  USE_EDITOR
		pMaterial->OnDeserialize(doc, root);
#endif
		return pMaterial;
	}
	return nullptr;
}

bool MaterialLoader::Destroy(Material*& p_material)
{
	return true;
}