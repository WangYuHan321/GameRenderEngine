#include "EditorResource.h"

#include "../../Render/Resource/Loader/TextureLoader.h"
#include "../../Render/Resource/Loader/ModelLoader.h"
#include "../../Render/Resource/Loader/ShaderLoader.h"
#include "../../Render/Resource/RawShader.h"

EditorResource::EditorResource(const std::string& p_editorAssetPath)
{
	std::string modelFolder = p_editorAssetPath + "\\Models\\";
	std::string iconsFolder = p_editorAssetPath + "\\Texture\\";

	EModelParserFlags modelParserFlags = EModelParserFlags::NONE;
	modelParserFlags |= EModelParserFlags::TRIANGULATE;
	modelParserFlags |= EModelParserFlags::GEN_SMOOTH_NORMALS;
	modelParserFlags |= EModelParserFlags::OPTIMIZE_MESHES;
	modelParserFlags |= EModelParserFlags::OPTIMIZE_GRAPH;
	modelParserFlags |= EModelParserFlags::FIND_INSTANCES;
	modelParserFlags |= EModelParserFlags::CALC_TANGENT_SPACE;
	modelParserFlags |= EModelParserFlags::JOIN_IDENTICAL_VERTICES;
	modelParserFlags |= EModelParserFlags::DEBONE;
	modelParserFlags |= EModelParserFlags::FIND_INVALID_DATA;
	modelParserFlags |= EModelParserFlags::IMPROVE_CACHE_LOCALITY;
	modelParserFlags |= EModelParserFlags::GEN_UV_COORDS;
	modelParserFlags |= EModelParserFlags::PRE_TRANSFORM_VERTICES;
	modelParserFlags |= EModelParserFlags::GLOBAL_SCALE;

	m_models["Plane"] = ModelLoader::getInstance()->Create(modelFolder + "Plane.fbx", modelParserFlags);
	m_models["Cube"] = ModelLoader::getInstance()->Create(modelFolder + "Cube.fbx", modelParserFlags);
	m_models["Cylinder"] = ModelLoader::getInstance()->Create(modelFolder + "Cylinder.fbx", modelParserFlags);
	m_models["Vertical_Plane"] = ModelLoader::getInstance()->Create(modelFolder + "Vertical_Plane.fbx", modelParserFlags);
	m_models["Roll"] = ModelLoader::getInstance()->Create(modelFolder + "Roll.fbx", modelParserFlags);
	m_models["Sphere"] = ModelLoader::getInstance()->Create(modelFolder + "Sphere.fbx", modelParserFlags);
	m_models["Arrow_Translate"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Translate.fbx", modelParserFlags);
	m_models["Arrow_Rotate"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Rotate.fbx", modelParserFlags);
	m_models["Arrow_Scale"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Scale.fbx", modelParserFlags);
	m_models["Arrow_Picking"] = ModelLoader::getInstance()->Create(modelFolder + "Arrow_Picking.fbx", modelParserFlags);
	m_models["Camera"] = ModelLoader::getInstance()->Create(modelFolder + "Camera.fbx", modelParserFlags);

	auto gridsSource = RawShader::GetGrid();
	auto gizmoSource = RawShader::GetGrizmo();
	m_shaders["Grid"] = ShaderLoader::getInstance()->CreateFromSource("Grid Shader", gridsSource.first, gridsSource.second);
	m_shaders["Gizmo"] = ShaderLoader::getInstance()->CreateFromSource("Gizmo Shader", gizmoSource.first, gizmoSource.second);

	std::string icon1 = iconsFolder + std::string("ButtonPlay.jpg");
	m_textures["Button_Play"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Button_Pause"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Button_Stop"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Button_Next"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);

	std::string icon_folder = iconsFolder + std::string("icon_folder.tga");
	std::string icon_folder_selected = iconsFolder + std::string("icon_folder_selected.tga");
	std::string icon_model = iconsFolder + std::string("icon_Model.png");
	std::string icon_texture = iconsFolder + std::string("icon_Texture.png");
	std::string icon_shader = iconsFolder + std::string("icon_Shader.png");
	std::string icon_material = iconsFolder + std::string("icon_Material.png");
	std::string icon_sound = iconsFolder + std::string("icon_Sound.png");
	std::string icon_scene = iconsFolder + std::string("icon_Scene.png");
	std::string icon_script = iconsFolder + std::string("icon_Script.png");
	std::string icon_font = iconsFolder + std::string("icon_Font.png");
	
	m_textures["Icon_Folder"] = TextureLoader::getInstance()->Create(icon_folder, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Folder_SELECTED"] = TextureLoader::getInstance()->Create(icon_folder_selected, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Model"] = TextureLoader::getInstance()->Create(icon_model, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Texture"] = TextureLoader::getInstance()->Create(icon_texture, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Shader"] = TextureLoader::getInstance()->Create(icon_shader, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Material"] = TextureLoader::getInstance()->Create(icon_material, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Sound"] = TextureLoader::getInstance()->Create(icon_sound, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Scene"] = TextureLoader::getInstance()->Create(icon_scene, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Script"] = TextureLoader::getInstance()->Create(icon_script, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Font"] = TextureLoader::getInstance()->Create(icon_font, GL_TEXTURE_2D, GL_RGBA);
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