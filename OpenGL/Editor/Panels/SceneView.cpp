#include "SceneView.h"
#include "../../Render/ForwardRenderer.h"
#include "../../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../UI/Visual/Image.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../File/Path/PathParser.h"

//#define EDITOR_USE_RAY //鼠标移动是否开启射线击中物体
//
//#define EDITOR_USE_TEXTURE //鼠标移动是否支持纹理检测击中物体

SceneView::SceneView(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSettings
		):
	AViewControllable(p_title, p_opened, p_windowSettings)
{
	m_img->AddPlugin<DDTarget<std::pair<std::string, Group*>>>("File").DataReceivedEvent += [this](auto data)
	{
		std::string path = data.first;

		switch (PathParser::getInstance()->GetFileType(path))
		{
		case EFileType::MODEL: LOG_INFO("Load Model" + path); break;
		case EFileType::SCENE: LOG_INFO("Load Scene" + path); break;
		}


	};

	m_camera.SetPerspective(Deg2Rad(60.0f), 0.5, 0.1f, 5000.0f);
	m_actorPickRenderTarget  = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, true);
}

SceneView::~SceneView()
{
	if(m_actorPickRenderTarget)
		delete m_actorPickRenderTarget;
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
	HandleActorPicking();
	RenderScene(glState);
	//ray
	//HandleActorPicking_Ray();
}

void SceneView::RenderScene(uint8_t p_defaultRenderState)
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	uint8_t state = baseRenderer.FetchGLState();

	m_editorRenderer.UpdateLights(*EDITOR_CONTEXT(m_sceneMgr)->GetActiveScene());

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
		m_editorRenderer.RenderLights();

		m_editorRenderer.RenderScene(m_camPos, m_camera);

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

		if (m_highlightedActor.has_value())//鼠标移动到
		{
			m_editorRenderer.RenderActorOutlinePass(m_highlightedActor.value().get(), true, false);
			baseRenderer.ApplyStateMask(p_defaultRenderState);
			m_editorRenderer.RenderActorOutlinePass(m_highlightedActor.value().get(), false, false);
		}
	}

	m_renderTarget->Unbind();
}

void SceneView::RenderSceneForActorPicking()
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	auto [winWidth, winHeight] = GetSafeSize();

	if (winWidth > 0 && winHeight > 0)
	{
		m_actorPickRenderTarget->Resize(winWidth, winHeight);
		m_actorPickRenderTarget->Bind();

		baseRenderer.SetStencilMask(0xFF);
		glClearColor(1, 1, 1, 1);
		baseRenderer.Clear();
		baseRenderer.SetStencilMask(0x00);
		m_editorRenderer.RenderSceneForActorPicking();


		if (EDITOR_EXEC(IsAnyActorSelected()))
		{
			auto& selectedActor = EDITOR_EXEC(GetSelectedActor());
			m_editorRenderer.RenderGizmo((Vector3&)selectedActor.m_transform.GetWorldPosition(),
				(Quaternion&)selectedActor.m_transform.GetWorldRotation(), m_currentOperation, true);
		}

		m_actorPickRenderTarget->Unbind();
	}

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
			auto& inputManager = *EDITOR_CONTEXT(m_inputMgr);

			auto [mouseX, mouseY] = inputManager.GetMousePosition();
			mouseX -= m_position.x;
			mouseY -= m_position.y;
			mouseY = GetSafeSize().y - mouseY + 25;

			m_actorPickRenderTarget->Bind();
			uint8_t pixel[3];
			dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get())->ReadPixels(static_cast<int>(mouseX), static_cast<int>(mouseY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
			m_actorPickRenderTarget->Unbind();

			uint32_t actorID = (0 << 24) | (pixel[2] << 16) | (pixel[1] << 8) | (pixel[0] << 0);
			auto actorUnderMouse = EDITOR_CONTEXT(m_sceneMgr)->GetActiveScene()->FindActorByID(actorID);

			if(actorUnderMouse != nullptr)
				m_highlightedActor = std::ref(*actorUnderMouse);
		
			/* Click */
			if (EDITOR_CONTEXT(m_inputMgr)->IsMouseButtonPressed(EMouseButton::MOUSE_BUTTON_LEFT))
			{
				if (actorUnderMouse)
				{
					EDITOR_EXEC(SelectActor(*actorUnderMouse));
				}
				else
				{
					EDITOR_EXEC(UnselectActor());
				}

			}
		}
	}
}


void SceneView::HandleActorPicking_Ray()
{
	if (IsHovered())
	{
		RenderSceneForActorPicking();

		if (!m_cameraController.IsRightMousePressed())
		{
			auto& inputMgr = *EDITOR_CONTEXT(m_inputMgr);
			auto [mouseX, mouseY] = inputMgr.GetMousePosition();
			mouseX -= m_position.x;
			mouseY -= m_position.y;
			mouseY = GetSafeSize().y - mouseY + 25;

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
