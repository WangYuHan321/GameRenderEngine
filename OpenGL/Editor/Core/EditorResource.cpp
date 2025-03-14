#include "EditorResource.h"

#include "../../Render/Resource/Loader/TextureLoader.h"
#include "../../Render/Resource/Loader/ModelLoader.h"
#include "../../Render/Resource/Loader/ShaderLoader.h"
#include "../../Editor/Helper/GUIDrawer.h"
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
	auto billSource = RawShader::GetBillboard();
	m_shaders["Grid"] = ShaderLoader::getInstance()->CreateFromSource("Grid Shader", gridsSource.first, gridsSource.second);
	m_shaders["Gizmo"] = ShaderLoader::getInstance()->CreateFromSource("Gizmo Shader", gizmoSource.first, gizmoSource.second);
	m_shaders["Billboard"] = ShaderLoader::getInstance()->CreateFromSource("Billboard Shader", billSource.first, billSource.second);

	std::string icon1 = iconsFolder + std::string("ButtonPlay.jpg");
	m_textures["Button_Play"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Button_Pause"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Button_Stop"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Button_Next"] = TextureLoader::getInstance()->Create(icon1, GL_TEXTURE_2D, GL_RGBA);

	std::string icon_folder = iconsFolder + std::string("icon_folder.tga");
	std::string icon_folder_selected = iconsFolder + std::string("icon_folder_selected.tga");
	std::string icon_model = iconsFolder + std::string("icon_model.png");
	std::string icon_texture = iconsFolder + std::string("icon_texture.png");
	std::string icon_shader = iconsFolder + std::string("icon_shader.png");
	std::string icon_material = iconsFolder + std::string("icon_material.png");
	std::string icon_sound = iconsFolder + std::string("icon_sound.png");
	std::string icon_scene = iconsFolder + std::string("icon_scene.png");
	std::string icon_script = iconsFolder + std::string("icon_script.png");
	std::string icon_font = iconsFolder + std::string("icon_font.png");

	std::string icon_directLight = iconsFolder + std::string("icon_dirLight.png");
	std::string icon_pointLight = iconsFolder + std::string("icon_pointLight.png");
	std::string icon_skyLight = iconsFolder + std::string("icon_skyLight.png");
	std::string icon_spotLight = iconsFolder + std::string("icon_spotLight.png");

	std::string icon_clock = iconsFolder + std::string("icon_clock.png");
	std::string icon_leftPlay = iconsFolder + std::string("icon_left.png");
	std::string icon_play = iconsFolder + std::string("icon_play.png");
	std::string icon_stop = iconsFolder + std::string("icon_stop.png");
	std::string icon_pause = iconsFolder + std::string("icon_pause.png");
	std::string icon_sequencer = iconsFolder + std::string("icon_sequencer.png");
	std::string icon_sequencerLine = iconsFolder + std::string("icon_sequencer_line.png");
	
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

	m_textures["Icon_DirectionlLight"] = TextureLoader::getInstance()->Create(icon_directLight, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_PointLight"] = TextureLoader::getInstance()->Create(icon_pointLight, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_SkyLight"] = TextureLoader::getInstance()->Create(icon_skyLight, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_SpotLight"] = TextureLoader::getInstance()->Create(icon_spotLight, GL_TEXTURE_2D, GL_RGBA);

	m_textures["Icon_Clock"] = TextureLoader::getInstance()->Create(icon_clock, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_LeftPlay"] = TextureLoader::getInstance()->Create(icon_leftPlay, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Play"] = TextureLoader::getInstance()->Create(icon_play, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Stop"] = TextureLoader::getInstance()->Create(icon_stop, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_Pause"] = TextureLoader::getInstance()->Create(icon_pause, GL_TEXTURE_2D, GL_RGBA);

	m_textures["Icon_Sequencer"] = TextureLoader::getInstance()->Create(icon_sequencer, GL_TEXTURE_2D, GL_RGBA);
	m_textures["Icon_SequencerLine"] = TextureLoader::getInstance()->Create(icon_sequencerLine, GL_TEXTURE_2D, GL_RGBA);

	m_textures["Empty_Texture"] = TextureLoader::getInstance()->CreateColor((255 << 24) | (255 << 16) | (255 << 8) | 255, GL_NEAREST, GL_NEAREST, false);
	GUIDrawer::ProvideEmptyTexture(*m_textures["Empty_Texture"]);
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