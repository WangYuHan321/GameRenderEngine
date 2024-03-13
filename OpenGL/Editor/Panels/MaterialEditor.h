#pragma once

#include "../../UI/Layout/Columns.h"
#include "../../UI/Panel/PanelWindow.h"

class Text;
class CShader;
class Material;
class GroupCollapsable;

class MaterialEditor : public PanelWindow
{
public:
	MaterialEditor
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_panelSetting
	);

	void CreateHeaderButtons();
	void CreateMaterialSelector();
	void CreateShaderSelector();

	void CreateMaterialSetting();
	void CreateShaderSetting();

	void GenerateShaderSettingContent();
	void GenerateMaterialSettingContent();
private:

	Material* m_target = nullptr;
	CShader* m_shader = nullptr;

	GroupCollapsable* m_shaderSetting;
	GroupCollapsable* m_materialSetting;

	Columns<2>* m_shaderSettingColumn;
	Columns<2>*m_materialSettingColumn;

	Event<> m_materialDroppedEvent;
	Event<> m_shaderDroppedEvent;


};

