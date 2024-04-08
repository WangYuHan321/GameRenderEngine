#include "DebugView.h"
#include"../Core/EditorAction.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CCamera.h"
#include"../../Render/RenderTarget.h"
#include "../../UI/Visual/Image.h"

DebugView::DebugView
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSettings
) :
	AView(p_title, p_opened, p_windowSettings),
	m_inputMgr(*EDITOR_CONTEXT(m_inputMgr))
{
	ImVec2 size = GetSafeSize();
	m_img = &CreateWidget<Image>(0, size);
}

void DebugView::Update(float p_deltaTime)
{
	AView::Update(p_deltaTime);

	if (m_inputMgr.IsKeyReleased(EKey::KEY_F1))
	{
		m_img->size = GetSafeSize();
		m_img->textureID.ID = EDITOR_CONTEXT(m_shadowMap).get()->GetShadowMap(0);
	}
	if (m_inputMgr.IsKeyReleased(EKey::KEY_F2))
	{
		m_img->size = GetSafeSize();
		m_img->textureID.ID = EDITOR_CONTEXT(m_shadowMap).get()->GetShadowMap(1);
	}
}

void DebugView::_Render_Impl()
{
}