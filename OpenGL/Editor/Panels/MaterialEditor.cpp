#include "MaterialEditor.h"
#include "../../UI/Visual/Separator.h"
#include "../../UI/Widgets/Button/Button.h"
#include "../../UI/Widgets/Text/Text.h"
#include "../../UI/Widgets/Selection/ComboBox.h"
#include "../../Editor/Helper/GUIDrawer.h"
#include "../../Render/Shader/EShader.h"
#include "../../Render/Resource/Loader/MaterialLoader.h"
#include "../../UI/Layout/GroupCollapsable.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../File/Path/PathParser.h"
#include <any>

void DrawCombox(WidgetContainer& p_root, const std::string& p_name, DepthFunc& p_depthTest)
{
	GUIDrawer::CreateTitle(p_root, p_name);
	auto& item = p_root.CreateWidget<ComboBox>(7);

	item.choices[0] = "OpenGL_LESS";
	item.choices[1] = "OpenGL_NEVER";
	item.choices[2] = "OpenGL_EQUAL";
	item.choices[3] = "OpenGL_GREATER";
	item.choices[4] = "OpenGL_NOTEQUAL";
	item.choices[5] = "OpenGL_GEQUAL";
	item.choices[6] = "OpenGL_ALWAYS";

	item.ValueChangedEvent += [&p_depthTest](int id)
	{
		switch (id)
		{
		case 0: p_depthTest = DepthFunc::OpenGL_LESS; break;
		case 1: p_depthTest = DepthFunc::OpenGL_NEVER; break;
		case 2: p_depthTest = DepthFunc::OpenGL_EQUAL; break;
		case 3: p_depthTest = DepthFunc::OpenGL_GREATER; break;
		case 4: p_depthTest = DepthFunc::OpenGL_NOTEQUAL; break;
		case 5: p_depthTest = DepthFunc::OpenGL_GEQUAL; break;
		case 6: p_depthTest = DepthFunc::OpenGL_ALWAYS; break;
		}
	};
}

void DrawCombox(WidgetContainer& p_root, const std::string& p_name, BlendParam& p_blendParam)
{
	GUIDrawer::CreateTitle(p_root, p_name);

	auto& item = p_root.CreateWidget<ComboBox>(7);
	item.choices[0] = "OpenGL_ZERO";
	item.choices[1] = "OpenGL_ONE";
	item.choices[2] = "OpenGL_SRC_COLOR";
	item.choices[3] = "OpenGL_ONE_MINUS_SRC_COLOR";
	item.choices[4] = "OpenGL_DST_COLOR";
	item.choices[5] = "OpenGL_ONE_MINUS_DST_COLOR";
	item.choices[6] = "OpenGL_SRC_ALPHA";
	item.choices[7] = "OpenGL_ONE_MINUS_SRC_ALPHA";
	item.choices[8] = "OpenGL_DST_ALPHA";
	item.choices[9] = "OpenGL_ONE_MINUS_DST_ALPHA";
	item.choices[10] = "OpenGL_CONSTANT_COLOR";
	item.choices[11] = "OpenGL_ONE_MINUS_CONSTANT_COLOR";
	item.choices[12] = "OpenGL_CONSTANT_ALPHA";
	item.choices[13] = "OpenGL_ONE_MINUS_CONSTANT_ALPHA";
	item.choices[14] = "OpenGL_SRC_ALPHA_SATURATE";

	item.ValueChangedEvent += [&p_blendParam](int id)
	{
		switch (id)
		{
		case 0: p_blendParam = BlendParam::OpenGL_ZERO; break;
		case 1: p_blendParam = BlendParam::OpenGL_ONE; break;
		case 2: p_blendParam = BlendParam::OpenGL_SRC_COLOR; break;
		case 3: p_blendParam = BlendParam::OpenGL_ONE_MINUS_SRC_COLOR; break;
		case 4: p_blendParam = BlendParam::OpenGL_DST_COLOR; break;
		case 5: p_blendParam = BlendParam::OpenGL_ONE_MINUS_DST_COLOR; break;
		case 6: p_blendParam = BlendParam::OpenGL_SRC_ALPHA; break;
		case 7: p_blendParam = BlendParam::OpenGL_ONE_MINUS_SRC_ALPHA; break;
		case 8: p_blendParam = BlendParam::OpenGL_DST_ALPHA; break;
		case 9: p_blendParam = BlendParam::OpenGL_ONE_MINUS_DST_ALPHA; break;
		case 10: p_blendParam = BlendParam::OpenGL_CONSTANT_COLOR; break;
		case 11: p_blendParam = BlendParam::OpenGL_ONE_MINUS_CONSTANT_COLOR; break;
		case 12: p_blendParam = BlendParam::OpenGL_CONSTANT_ALPHA; break;
		case 13: p_blendParam = BlendParam::OpenGL_ONE_MINUS_CONSTANT_ALPHA; break;
		case 14: p_blendParam = BlendParam::OpenGL_SRC_ALPHA_SATURATE; break;
		}
	};
}

void DrawCombox(WidgetContainer& p_root, const std::string& p_name, BlendFunc& p_blendFunc)
{
	GUIDrawer::CreateTitle(p_root, p_name);
	auto& item = p_root.CreateWidget<ComboBox>(5);
	item.choices[0] = "OpenGL_FUNC_ADD";
	item.choices[1] = "OpenGL_FUNC_SUBTRACT";
	item.choices[2] = "OpenGL_FUNC_REVERSE_SUBTRACT";
	item.choices[3] = "OpenGL_MIN";
	item.choices[4] = "OpenGL_MAX";

	item.ValueChangedEvent += [&p_blendFunc](int id)
	{
		switch (id)
		{
		case 0: p_blendFunc = BlendFunc::OpenGL_FUNC_ADD; break;
		case 1: p_blendFunc = BlendFunc::OpenGL_FUNC_SUBTRACT; break;
		case 2: p_blendFunc = BlendFunc::OpenGL_FUNC_REVERSE_SUBTRACT; break;
		case 3: p_blendFunc = BlendFunc::OpenGL_MIN; break;
		case 4: p_blendFunc = BlendFunc::OpenGL_MAX; break;
		}
	};
}

void DrawCombox(WidgetContainer& p_root, const std::string& p_name, CullFace& p_cullFace)
{
	GUIDrawer::CreateTitle(p_root, p_name);
	auto& item = p_root.CreateWidget<ComboBox>(3);
	item.choices[0] = "OpenGL_FRONT";
	item.choices[1] = "OpenGL_BACK";
	item.choices[2] = "OpenGL_FRONT_AND_BACKT";

	item.ValueChangedEvent += [&p_cullFace](int id)
	{
		switch (id)
		{
		case 0: p_cullFace = CullFace::OpenGL_FRONT; break;
		case 1: p_cullFace = CullFace::OpenGL_BACK; break;
		case 2: p_cullFace = CullFace::OpenGL_FRONT_AND_BACKT; break;
		}
	};
}

void DrawCombox(WidgetContainer& p_root, const std::string& p_name, FrontFace& p_frontFace)
{
	GUIDrawer::CreateTitle(p_root, p_name);
	auto& item = p_root.CreateWidget<ComboBox>(2);
	item.choices[0] = "OpenGL_CW";
	item.choices[1] = "OpenGL_CCW";

	item.ValueChangedEvent += [&p_frontFace](int id)
	{
		switch (id)
		{
		case 0: p_frontFace = FrontFace::OpenGL_CW; break;
		case 1: p_frontFace = FrontFace::OpenGL_CCW; break;
		}
	};
}

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


	m_materialDroppedEvent += std::bind(&MaterialEditor::OnMateiralDropped, this);
	m_shaderDroppedEvent += std::bind(&MaterialEditor::OnShaderDropped, this);
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
	m_shaderContent = &GUIDrawer::DrawShader(columns, EDITOR_LANGUAGE(SHADER_TEXT), m_shader, &m_shaderDroppedEvent);
}


void MaterialEditor::CreateMaterialSetting()
{
	m_materialSetting = &CreateWidget<GroupCollapsable>(EDITOR_LANGUAGE(MATERIAL_SETTING));
	m_materialSettingColumn = &m_materialSetting->CreateWidget<Columns<2>>();
	m_materialSettingColumn->widths[0] = 150;
}

void MaterialEditor::OnMateiralDropped()
{
	GenerateMaterialSettingContent();
}

void MaterialEditor::OnShaderDropped()
{
	GenerateShaderSettingContent();
}

void MaterialEditor::CreateShaderSetting()
{
	m_shaderSetting = &CreateWidget<GroupCollapsable>(EDITOR_LANGUAGE(SHADER_SETTING));
	m_shaderSettingColumn = &m_shaderSetting->CreateWidget<Columns<2>>();
	m_shaderSettingColumn->widths[0] = 150;
}

void MaterialEditor::GenerateShaderSettingContent()
{
	m_shaderSettingColumn->RemoveAllWidgets();

	std::multimap<int, std::pair<std::string, UniformValue>> sortedUniformData1;
	std::multimap<int, std::pair<std::string, UniformSampler>> sortedUniformData2;

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
		sortedUniformData1.emplace(orderID, std::pair<std::string, UniformValue>(name, value));
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
		sortedUniformData2.emplace(orderID, std::pair<std::string, UniformSampler>(name, value));
	}

	for (auto& [order, info] : sortedUniformData2)
	{
		if (UniformSampler* pValue = reinterpret_cast<UniformSampler*>(&info.second); pValue)
		{
			switch (pValue->Type)
			{
			//case SHADER_TYPE::SHADER_SAMPLER1D: GUIDrawer::DrawS; break;
			//case SHADER_TYPE::SHADER_SAMPLER2D: GUIDrawer::DrawTexture = 2; break;
			//case SHADER_TYPE::SHADER_SAMPLER3D: orderID = 1; break;
			//case SHADER_TYPE::SHADER_SAMPLERCUBE: orderID = 0; break;
			}
		}
	}

	for (auto& [order, info] : sortedUniformData1)
	{
		if (UniformValue* pValue = reinterpret_cast<UniformValue*>(&info.second); pValue)
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
	m_materialSettingColumn->RemoveAllWidgets();

	GUIDrawer::DrawBoolean(*m_materialSettingColumn, "DepthTest", m_target->DepthTest);
	GUIDrawer::DrawBoolean(*m_materialSettingColumn, "DepthWrite", m_target->DepthWrite);
	DrawCombox(*m_materialSettingColumn, "DepthFunc", (DepthFunc&)(m_target->DepthCompare));

	GUIDrawer::DrawBoolean(*m_materialSettingColumn, "Cull", m_target->Cull);
	DrawCombox(*m_materialSettingColumn, "CullFace", (CullFace&)m_target->CullFace);
	DrawCombox(*m_materialSettingColumn, "DepthFunc", (FrontFace&)(m_target->CullWindingOrder));

	GUIDrawer::DrawBoolean(*m_materialSettingColumn, "Blend", m_target->Blend);
	DrawCombox(*m_materialSettingColumn, "CullFace (src)", (CullFace&)m_target->BlendSrc);
	DrawCombox(*m_materialSettingColumn, "CullFace (Dst)", (CullFace&)m_target->BlendDst);
	DrawCombox(*m_materialSettingColumn, "DepthFunc", (FrontFace&)(m_target->BlendEquation));

	GUIDrawer::DrawBoolean(*m_materialSettingColumn, "ColorWrite", m_target->ColorWrite);
	
	GUIDrawer::DrawBoolean(*m_materialSettingColumn, "ShadowCast", m_target->ShadowCast);
	GUIDrawer::DrawBoolean(*m_materialSettingColumn, "ShadowReceive", m_target->ShadowReceive);

	GUIDrawer::DrawScalar<int>(*m_materialSettingColumn, "GPU Instances", (int&)m_target->GPUInstance, 1.0f, 0, 100000);

	if (m_target->GetShader() != nullptr)
	{
		m_shader = m_target->GetShader();
		m_shaderContent->content = PathParser::getInstance()->GetFileNameByPath(m_shader->GetShaderPath());
		OnShaderDropped();
	}
}

