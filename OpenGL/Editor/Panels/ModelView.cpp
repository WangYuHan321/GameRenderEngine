#include "ModelView.h"
#include "../../Core/ECS/Actor.h"
#include "../../Render/Mesh/Model.h"
#include "../../UI/Visual/Image.h"
#include "../../Render/Mesh/Material.h"
#include "../../Render/ForwardRenderer.h"
#include "../../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../UI/Visual/Image.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../File/Path/PathParser.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Render/Resource/Loader/ModelLoader.h"
#include "../../UI/Layout/TreeNode.h"
#include "../../UI/Widgets/InputField/InputText.h"
#include "../../UI/Layout/GroupCollapsable.h"

std::vector<TreeNode*> _founds;

ModelView::ModelView
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting
) : AViewControllable(p_title, p_opened, p_panelSetting)
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

	m_groupCollapsable = &CreateWidget<GroupCollapsable>("Hierarchy");
	m_img->SetParent(m_groupCollapsable);

	InitHierarchy();

	m_camera.SetPerspective(Deg2Rad(60.0f), 0.5, 0.1f, 5000.0f);
	m_actorPickRenderTarget = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, true);

	m_curActor = &GLOBALSERVICE(EditorAction).CreateActorWithModel("../../Engine/Asset/meshes/sponza/sponza.obj", false);
}

ModelView::~ModelView()
{
}

void ModelView::_Render_Impl()
{
	PrepareCamera();
	HandleActorPicking();
	RenderScene();
}

void ModelView::RenderSceneForActorPicking()
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	ImVec2 size(GetSafeSize());

	if (size.x > 0 && size.y > 0)
	{
		m_actorPickRenderTarget->Resize(size.x, size.y);
		m_actorPickRenderTarget->Bind();

		baseRenderer.SetStencilMask(0xFF);
		glClearColor(1, 1, 1, 1);
		baseRenderer.Clear();
		baseRenderer.SetStencilMask(0x00);
		dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get())->SetViewPort(0, 0, size.x, size.y);

		m_editorRenderer.RenderSceneForActorPicking();


		//if (EDITOR_EXEC(IsAnyActorSelected()))
		//{
		//	auto& selectedActor = EDITOR_EXEC(GetSelectedActor());
		//	m_editorRenderer.RenderGizmo((Vector3&)selectedActor.m_transform.GetWorldPosition(),
		//		(Quaternion&)selectedActor.m_transform.GetWorldRotation(), m_currentOperation, true);
		//}

		m_actorPickRenderTarget->Unbind();
	}

}

void ModelView::HandleActorPicking()
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
			mouseY = GetSafeSize().y - mouseY + 40;

			m_actorPickRenderTarget->Bind();
			uint8_t pixel[3];
			dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get())->ReadPixels(static_cast<int>(mouseX), static_cast<int>(mouseY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
			m_actorPickRenderTarget->Unbind();

			uint32_t actorID = (0 << 24) | (pixel[2] << 16) | (pixel[1] << 8) | (pixel[0] << 0);
			auto actorUnderMouse = EDITOR_CONTEXT(m_sceneMgr)->GetActiveScene()->FindActorByID(actorID);

			if (actorUnderMouse != nullptr)
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

void ModelView::Update(float deltaTime)
{
	AViewControllable::Update(deltaTime);
}

void ModelView::RenderScene()
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());
	auto& editorResource = *dynamic_cast<EditorResource*>(EDITOR_CONTEXT(m_editorResource).get());

	m_editorRenderer.UpdateLights(*EDITOR_CONTEXT(m_sceneMgr)->GetActiveScene());

	m_renderTarget->Bind();

	baseRenderer.SetStencilMask(0xFF);
	glClearColor(0.2, 0.2, 0.2, 1);
	baseRenderer.Clear();

	Vector3 c(0.176f, 0.176f, 0.176f);

	//m_editorRenderer.RenderActorOutlinePass(*m_curActor, false, false);
	m_editorRenderer.RenderGrid(m_camPos, c);
	m_editorRenderer.RenderActor(*m_curActor);

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
		int highlightedAxis = -1;
		m_editorRenderer.RenderActorOutlinePass(m_highlightedActor.value().get(), true, false);
		m_editorRenderer.RenderActorOutlinePass(m_highlightedActor.value().get(), false, false);

		highlightedAxis = static_cast<int>(m_highlightedGizmoDirection.value());

		auto& selectedActor = EDITOR_EXEC(GetSelectedActor());
	}

	m_renderTarget->Unbind();

}

void ModelView::InitHierarchy()
{
	auto& searchBar = m_groupCollapsable->CreateWidget<InputText>();
	searchBar.ContentChangedEvent += [this](const std::string& p_content)
	{
		_founds.clear();

		auto content = p_content;
		std::transform(content.begin(), content.end(), content.begin(), ::tolower); //tolower字母小写 将content 所有按顺序 放入content.begin()

		for (auto& [actor, item] : m_widgetBoneLink)
		{
			if (!p_content.empty())
			{
				auto itemName = item->name;
				std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

				if (itemName.find(content) != std::string::npos)
				{
					_founds.push_back(item);
				}

				item->enabled = false;
			}
			else
			{
				item->enabled = true;
			}
		}

		for (auto node : _founds)
		{
			node->enabled = true;
		}

	};

	m_sceneRoot = &m_groupCollapsable->CreateWidget<TreeNode>("Root", true);
	m_sceneRoot->Open();

	m_sceneRoot->AddPlugin< DDTarget<std::pair<Actor*, TreeNode*>> >("Actor").DataReceivedEvent += [this](std::pair<Actor*, TreeNode*> p_element)
	{
	};
}
