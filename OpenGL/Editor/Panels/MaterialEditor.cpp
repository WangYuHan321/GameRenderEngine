#include "MaterialEditor.h"
#include "../../UI/Visual/Separator.h"
#include "../../UI/Widgets/Button/Button.h"
#include "../../UI/Layout/Columns.h"
#include "../../Editor/Helper/GUIDrawer.h"
#include "../../Render/Shader/EShader.h"
#include "../../Render/Resource/Loader/MaterialLoader.h"

MaterialEditor::MaterialEditor(const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting) :
	PanelWindow(p_title, p_opened, p_panelSetting)
{
	CreateHeaderButtons();
	CreateWidget<Separator>();
	CreateMaterialSelector();
	CreateShaderSelector();
}

void MaterialEditor::CreateHeaderButtons()
{
	auto& saveToFileBtn = CreateWidget<Button>("Save To File");
	saveToFileBtn.idleColor = Color4(0.2, 0.5, 0.0, 1.0);
	saveToFileBtn.lineBreak = false;
	saveToFileBtn.ClickedEvent += [this] {
		if (m_target)
		{
			LOG_INFO("save to file");
			//MaterialLoader::getInstance()->
		}
	};

	auto& reloadToFileBtn = CreateWidget<Button>("Reload To File");
	reloadToFileBtn.idleColor = Color4(0.2, 0.5, 0.0, 1.0);
	reloadToFileBtn.lineBreak = false;
	reloadToFileBtn.ClickedEvent += [this] {
		if (m_target)
		{
			LOG_INFO("reload to file");
			//MaterialLoader::getInstance()->
		}
	};

	auto& previewToFileBtn = CreateWidget<Button>("Preview To File");
	previewToFileBtn.idleColor = Color4(0.2, 0.5, 0.0, 1.0);
	previewToFileBtn.lineBreak = false;
	previewToFileBtn.ClickedEvent += [this] {
		if (m_target)
		{
			LOG_INFO("Preview to file");
			//MaterialLoader::getInstance()->
		}
	};

	auto& resetToFileBtn = CreateWidget<Button>("Reset To File");
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
	GUIDrawer::DrawMaterial(columns, "Material", m_target, nullptr);
}

void MaterialEditor::CreateShaderSelector()
{
	auto& columns = CreateWidget<Columns<2>>();
	columns.widths[0] = 150;
	GUIDrawer::DrawShader(columns, "Shader", m_shader, nullptr);
}
