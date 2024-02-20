#include "EditorResource.h"

#include "../../Render/Resource/Loader/TextureLoader.h"
#include "../../Render/Resource/Loader/ModelLoader.h"
#include "../../Render/Resource/Loader/ShaderLoader.h"

EditorResource::EditorResource(const std::string& p_editorAssetPath)
{
	std::string modelFolder = p_editorAssetPath + "Models\\";

	m_models["Cube"] = ModelLoader::getInstance()->Create(modelFolder + "Cube.fbx");
	m_models["Cylinder"] = ModelLoader::getInstance()->Create(modelFolder + "Cylinder.fbx");
	m_models["Plane"] = ModelLoader::getInstance()->Create(modelFolder + "Plane.fbx");
	m_models["Vertical_Plane"] = ModelLoader::getInstance()->Create(modelFolder + "Vertical_Plane.fbx");
	m_models["Roll"] = ModelLoader::getInstance()->Create(modelFolder + "Roll.fbx");
	m_models["Sphere"] = ModelLoader::getInstance()->Create(modelFolder + "Sphere.fbx");
	m_models["Arrow_Translate"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Translate.fbx");
	m_models["Arrow_Rotate"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Rotate.fbx");
	m_models["Arrow_Scale"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Scale.fbx");
	m_models["Arrow_Picking"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Picking.fbx");
	m_models["Camera"] = ModelLoader::getInstance()->Create(modelFolder + "Camera.fbx");
}

EditorResource::~EditorResource()
{
	for (auto [id, model] : m_models)
		ModelLoader::getInstance()->Destroy(model);

	for (auto [id, texture] : m_textures)
		TextureLoader::getInstance()->Destroy(texture);

	for (auto [id, shader] : m_shaders)
		ShaderLoader::getInstance()->Destroy(shader);
}

Model* EditorResource::GetModel(const std::string& p_modelName)
{
	if (m_models.find(p_modelName) != m_models.end())
		return m_models.at(p_modelName);

	return nullptr;
}

CShader* EditorResource::GetShader(const std::string& p_shaderName)
{
	if (m_shaders.find(p_shaderName) != m_shaders.end())
		return m_shaders.at(p_shaderName);

	return nullptr;
}

Texture* EditorResource::GetTexture(const std::string& p_textureName)
{
	if (m_textures.find(p_textureName) != m_textures.end())
		return m_textures.at(p_textureName);

	return nullptr;
}