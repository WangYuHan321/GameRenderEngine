#include "AssetView.h"
#include "../../Render/Forward/ForwardRenderer.h"
#include "../../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../UI/Visual/Image.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../File/Path/PathParser.h"

AssetView::AssetView(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSettings
) : 
	AViewControllable(p_title, p_opened, p_windowSettings)
{
	m_camera.ClearColor = (Color4( 0.098f, 0.098f, 0.098f, 1.0f ));
	m_camera.Far = (5000.0f);

	m_resource = static_cast<Model*>(nullptr);
}

void AssetView::_Render_Impl()
{
	PrepareCamera();

	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	m_renderTarget->Bind();

	baseRenderer.SetStencilMask(0xFF);
	baseRenderer.Clear(m_camera);
	baseRenderer.SetStencilMask(0x00);

	Vector3 c(0.176f, 0.176f, 0.176f);
	m_editorRenderer.RenderGrid(m_camPos, c);

	if (auto pval = std::get_if<Material*>(&m_resource); pval && *pval)
		m_editorRenderer.RenderMaterialAsset(**pval);

	m_renderTarget->Unbind();
}

void AssetView::SetResource(ViewableResource p_viewResource)
{
	m_resource = p_viewResource;
}

AssetView::~AssetView()
{

}

AssetView::ViewableResource AssetView::GetResource() const
{
	return m_resource;
}