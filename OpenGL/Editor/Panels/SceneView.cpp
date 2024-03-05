#include "SceneView.h"
#include "../../Render/ForwardRenderer.h"
#include "../../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CCamera.h"
SceneView::SceneView(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSettings
		):
	AViewControllable(p_title, p_opened, p_windowSettings)
{
	m_camera.SetPerspective(Deg2Rad(60.0f), 0.5, 0.1f, 5000.0f);
}

bool HitSphere(const Vector3& center, float radius, const Ray& r) {
	Vector3 oc = r.p0 - center;
	float a = glm::dot(r.dir, r.dir);//2
	float b = 2.0f * glm::dot(r.dir, oc);
	float c = dot(oc, oc) - radius * radius;
	float discriminate = b * b - 4 * a * c;
	if (discriminate < 0)
		return false;
	else
		return (-b - sqrtf(discriminate)) / (2.0f * a) > 0;//1
}

void SceneView::Update(float p_deltaTime)
{
	AViewControllable::Update(p_deltaTime);

}

void SceneView::_Render_Impl()
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	PrepareCamera();
	uint8_t glState = baseRenderer.FetchGLState();
	RenderScene(glState);
	HandleActorPicking();
}

void SceneView::RenderScene(uint8_t p_defaultRenderState)
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	uint8_t state = baseRenderer.FetchGLState();

	m_renderTarget->Bind();
	if (m_renderTarget->Width > 0 && m_renderTarget->Height > 0)
	{
		baseRenderer.SetStencilMask(0xFF);
		glClearColor(0.2, 0.2, 0.2, 1);
		baseRenderer.Clear();
		baseRenderer.SetStencilMask(0x00);

		Vector3 c(0.176f, 0.176f, 0.176f);
		m_editorRenderer.RenderGrid(m_camPos, c);
		m_editorRenderer.RenderCameras();

		if (EDITOR_EXEC(IsAnyActorSelected()))
		{
			auto& selectedActor = EDITOR_EXEC(GetSelectedActor());
			
			if (selectedActor.IsActive())
			{
				m_editorRenderer.RenderActorOutlinePass(selectedActor, true, true);
				m_editorRenderer.RenderActorOutlinePass(selectedActor, false, true);
			}

			baseRenderer.Clear(false, true, false);

			m_editorRenderer.RenderGizmo((Vector3&)selectedActor.m_transform.GetWorldPosition(),
				(Quaternion&)selectedActor.m_transform.GetWorldRotation(), m_currentOperation, false);
		}
	}

	m_renderTarget->Unbind();
}

void SceneView::RenderSceneForActorPicking()
{
	auto& baseRenderer = *EDITOR_CONTEXT(m_renderer).get();

	auto [winWidth, winHeight] = GetSafeSize();

	//m_actorPickRenderTarget->Resize(winWidth, winHeight);
	//m_actorPickRenderTarget->Bind();



	//m_actorPickRenderTarget->Unbind();
}

void SceneView::HandleActorPicking()
{
	if (IsHovered())
	{
		RenderSceneForActorPicking();

		m_highlightedActor = {};
		m_highlightedGizmoDirection = {};

		if (!m_cameraController.IsRightMousePressed())
		{
			auto& inputMgr = *EDITOR_CONTEXT(m_inputMgr);
			auto [mouseX, mouseY] = inputMgr.GetMousePosition();
			mouseX -= m_position.x;
			mouseY -= m_position.y;
			mouseY = /*GetSafeSize().y - */mouseY + 25;

			Vector2 ndcCoord;
			ndcCoord.x = ((2.0f * mouseX) / GetSafeSize().x) - 1.0f;
			ndcCoord.y = 1.0f - ((2.0f * mouseY) / GetSafeSize().y);

			Vector3 mouseWorldRay = GetScreenToWorldRay(ndcCoord, 0.01f, 1.0f, m_camera.View, m_camera.Projection);

			Ray ray;
			ray.p0 = ScreenToWorld(ndcCoord, 0.01f, m_camera.View, m_camera.Projection);
			ray.dir = mouseWorldRay;

			for (auto& sceneItem : EDITOR_CONTEXT(m_sceneMgr)->GetActiveScene()->GetActors())
			{
				if (sceneItem->GetComponent<CModelRenderer>())
				{
					BoundingSphere boundSphere = sceneItem->GetComponent<CModelRenderer>()->GetModel()->GetBoundingSphere();
					if (HitSphere(boundSphere.position, boundSphere.radius, ray))
					{
						//printf("当前鼠标选中物体为 %s", sceneItem->GetName().c_str());
					}
				}
				if (sceneItem->GetComponent<CCamera>())
				{
					BoundingSphere boundSphere = EDITOR_CONTEXT(m_editorResource)->GetModel("Camera")->GetBoundingSphere();
					if (HitSphere(sceneItem->GetComponent<CTransform>()->GetWorldPosition(), boundSphere.radius, ray))
					{
						m_renderTarget->Bind();
						m_editorRenderer.RenderActorOutlinePass(*sceneItem, true, false);
						m_editorRenderer.RenderActorOutlinePass(*sceneItem, false, false);
						m_renderTarget->Unbind();
					}
				}

			}

		}

	}


}