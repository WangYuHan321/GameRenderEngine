#include "MaterialLoader.h"
#include "ShaderLoader.h"
#include "../../../Util/common.h"
#include "../../Core/API/ISerializable.h"

Material MaterialLoader::LoadMaterial(std::string name, CShader* p_shader)
{
	return p_shader == nullptr ? Material() : Material(p_shader);
}

Material MaterialLoader::LoadMaterial(CShader* p_shader)
{
	return Material(p_shader);
}

void MaterialLoader::Save(Material& p_material, std::string p_path)
{
	tinyxml2::TinyXMLDocument doc;
	doc.LoadFile(p_path.c_str());

	if (!doc.Error())
	{
		doc.Clear();
		tinyxml2::XMLNode* pNode = doc.NewElement("root");
		doc.InsertFirstChild(pNode);
#ifdef USE_EDITOR
		p_material.OnSerialize(doc, pNode);
#endif
	}
	if (doc.SaveFile(p_path.c_str()) == tinyxml2::XML_SUCCESS)
		LOG_INFO("[MATERIAL] \"" + p_path + "\": Saved");
	else
		LOG_ERROR("[MATERIAL] \"" + p_path + "\": Failed to save");
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
		pMaterial->Path = p_path;

		return pMaterial;
	}
	return nullptr;
}

bool MaterialLoader::Destroy(Material*& p_material)
{
	return true;
}