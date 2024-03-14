#include "MaterialEditor.h"
#include "../../UI/Visual/Separator.h"
#include "../../UI/Widgets/Button/Button.h"
#include "../../Editor/Helper/GUIDrawer.h"
#include "../../Render/Shader/EShader.h"
#include "../../Render/Resource/Loader/MaterialLoader.h"
#include "../../UI/Layout/GroupCollapsable.h"
#include "../../Editor/Core/EditorAction.h"
#include <any>

MaterialEditor::MaterialEditor(const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting) :
	PanelWindow(p_title, p_opened, p_panelSetting)
{
	CreateHeaderButtons();
	CreateWidget<Separator>();
	CreateMaterialSelector();
	CreateShaderSelector();
	CreateMaterialSetting();
	CreateShaderSetting();


	m_materialDroppedEvent += [this]
	{

	};

	m_shaderDroppedEvent += [this]
	{

	};
}

void MaterialEditor::CreateHeaderButtons()
{
	auto& saveToFileBtn = CreateWidget<Button>(EDITOR_LANGUAGE(MATERIAL_EDITOR_SAVE));
	saveToFileBtn.idleColor = Color4(0.2, 0.5, 0.0, 1.0);
	saveToFileBtn.lineBreak = false;
	saveToFileBtn.ClickedEvent += [this] {
		if (m_target)
		{
			LOG_INFO("save to file");
			//MaterialLoader::getInstance()->
		}
	};

	auto& reloadToFileBtn = CreateWidget<Button>(EDITOR_LANGUAGE(MATERIAL_EDITOR_RELOAD));
	reloadToFileBtn.idleColor = Color4(0.2, 0.5, 0.0, 1.0);
	reloadToFileBtn.lineBreak = false;
	reloadToFileBtn.ClickedEvent += [this] {
		if (m_target)
		{
			LOG_INFO("reload to file");
			//MaterialLoader::getInstance()->
		}
	};

	auto& previewToFileBtn = CreateWidget<Button>(EDITOR_LANGUAGE(MATERIAL_EDITOR_PREVIEW));
	previewToFileBtn.idleColor = Color4(0.2, 0.5, 0.0, 1.0);
	previewToFileBtn.lineBreak = false;
	previewToFileBtn.ClickedEvent += [this] {
		if (m_target)
		{
			LOG_INFO("Preview to file");
			//MaterialLoader::getInstance()->
		}
	};

	auto& resetToFileBtn = CreateWidget<Button>(EDITOR_LANGUAGE(MATERIAL_EDITOR_RESET));
	resetToFileBtn.idleColor = Color4(0.2, 0.5, 0.0, 1.0);
	resetToFileBtn.lineBreak = false;
	resetToFileBtn.ClickedEvent += [this] {
		if (m_target)
		{
			LOG_INFO("Reset to file");
			//MaterialLoader::getInstance()->
		}
	};
}

void MaterialEditor::CreateMaterialSelector()
{
	auto& columns = CreateWidget<Columns<2>>();
	columns.widths[0] = 150;
	GUIDrawer::DrawMaterial(columns, EDITOR_LANGUAGE(MATERIAL_TEXT), m_target, &m_materialDroppedEvent);
}

void MaterialEditor::CreateShaderSelector()
{
	auto& columns = CreateWidget<Columns<2>>();
	columns.widths[0] = 150;
	GUIDrawer::DrawShader(columns, EDITOR_LANGUAGE(SHADER_TEXT), m_shader, &m_shaderDroppedEvent);
}


void MaterialEditor::CreateMaterialSetting()
{
	m_materialSetting = &CreateWidget<GroupCollapsable>(EDITOR_LANGUAGE(MATERIAL_SETTING));
	m_materialSettingColumn = &m_materialSetting->CreateWidget<Columns<2>>();
	m_materialSettingColumn->widths[0] = 150;
}

void MaterialEditor::CreateShaderSetting()
{
	m_shaderSetting = &CreateWidget<GroupCollapsable>(EDITOR_LANGUAGE(SHADER_SETTING));
	m_shaderSettingColumn = &m_materialSetting->CreateWidget<Columns<2>>();
	m_shaderSettingColumn->widths[0] = 150;
}

void MaterialEditor::GenerateShaderSettingContent()
{
	m_shaderSettingColumn->RemoveAllWidgets();

	std::multimap<int, std::pair<std::string, std::any>> sortedUniformData;

	int orderID = 0; //samplercube = 0 sampler3D = 1 sampler2d 2 sampler1d 3 mat4 4 mat3 5 mat2 6 vec4 7 vec3 8 vec2 9 float 10 int 11 bool 12

	for (auto& [name, value] : *m_target->GetUniforms())
	{
		switch (value.Type)
		{
		case SHADER_TYPE::SHADER_BOOL:  orderID = 12; break;
		case SHADER_TYPE::SHADER_FLOAT: orderID = 10; break;
		case SHADER_TYPE::SHADER_INT:   orderID = 11; break;
		case SHADER_TYPE::SHADER_VEC2:  orderID = 9; break;
		case SHADER_TYPE::SHADER_VEC3:  orderID = 8; break;
		case SHADER_TYPE::SHADER_VEC4:  orderID = 7; break;
		case SHADER_TYPE::SHADER_MAT2:  orderID = 6; break;
		case SHADER_TYPE::SHADER_MAT3:  orderID = 5; break;
		case SHADER_TYPE::SHADER_MAT4:  orderID = 4; break;
		}
		sortedUniformData.emplace(orderID, std::pair<std::string, std::any>(name, value));
	}

	for (auto& [name, value] : *m_target->GetSamplerUniforms())
	{
		switch (value.Type)
		{
		case SHADER_TYPE::SHADER_SAMPLER1D: orderID = 3; break; 
		case SHADER_TYPE::SHADER_SAMPLER2D: orderID = 2; break; 
		case SHADER_TYPE::SHADER_SAMPLER3D: orderID = 1; break; 
		case SHADER_TYPE::SHADER_SAMPLERCUBE: orderID = 0; break; 
		}
		sortedUniformData.emplace(orderID, std::pair<std::string, std::any>(name, value));
	}

	for (auto& [order, info] : sortedUniformData)
	{
		if (UniformSampler* pValue = (UniformSampler*)(&info.second); pValue)
		{
			switch (pValue->Type)
			{
			//case SHADER_TYPE::SHADER_SAMPLER1D: GUIDrawer::DrawS; break;
			//case SHADER_TYPE::SHADER_SAMPLER2D: GUIDrawer::DrawTexture = 2; break;
			//case SHADER_TYPE::SHADER_SAMPLER3D: orderID = 1; break;
			//case SHADER_TYPE::SHADER_SAMPLERCUBE: orderID = 0; break;
			}
		}

		if (UniformValue* pValue = (UniformValue*)(&info.second); pValue)
		{
			switch (pValue->Type)
			{
			case SHADER_TYPE::SHADER_BOOL:      GUIDrawer::DrawBoolean(*m_shaderSettingColumn, info.first, pValue->BOOL); break;
				case SHADER_TYPE::SHADER_FLOAT: GUIDrawer::DrawScalar(*m_shaderSettingColumn, info.first, pValue->FLOAT);; break;
				case SHADER_TYPE::SHADER_INT:   GUIDrawer::DrawScalar(*m_shaderSettingColumn, info.first, pValue->INT);; break;
				case SHADER_TYPE::SHADER_VEC2:  GUIDrawer::DrawVec2(*m_shaderSettingColumn, info.first, pValue->VEC2); break;
				case SHADER_TYPE::SHADER_VEC3:  GUIDrawer::DrawVec3(*m_shaderSettingColumn, info.first, pValue->VEC3);; break;
				case SHADER_TYPE::SHADER_VEC4:  GUIDrawer::DrawVec4(*m_shaderSettingColumn, info.first, pValue->VEC4); break;
				case SHADER_TYPE::SHADER_MAT2:  GUIDrawer::DrawBoolean(*m_shaderSettingColumn, info.first, pValue->BOOL); break;
				case SHADER_TYPE::SHADER_MAT3:  GUIDrawer::DrawBoolean(*m_shaderSettingColumn, info.first, pValue->BOOL); break;
				case SHADER_TYPE::SHADER_MAT4:  GUIDrawer::DrawBoolean(*m_shaderSettingColumn, info.first, pValue->BOOL); break;
			}
		}

	}
}

void MaterialEditor::GenerateMaterialSettingContent()
{

}

