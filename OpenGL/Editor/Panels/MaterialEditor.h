#pragma once

#include "../../UI/Panel/PanelWindow.h"

class Text;
class CShader;
class Material;

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

private:

	Material* m_target;
	CShader* m_shader;


};

