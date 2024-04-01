#include "ModelView.h"

ModelView::ModelView
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting
) : AViewControllable(p_title, p_opened, p_panelSetting)
{
}

ModelView::~ModelView()
{
}

void ModelView::_Render_Impl()
{

}