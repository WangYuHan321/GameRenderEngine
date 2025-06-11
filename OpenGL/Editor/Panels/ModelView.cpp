#include "ModelView.h"
#include "../../Core/ECS/Actor.h"
#include "../../Render/Mesh/Model.h"
#include "../../UI/Visual/Image.h"
#include "../../Render/Mesh/Material.h"
#include "../../Render/Forward/ForwardRenderer.h"
#include "../../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../UI/Visual/Image.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../File/Path/PathParser.h"
#include "../../Core/ECS/Components/CTransform.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"
#include "../../Render/Resource/Loader/ModelLoader.h"
#include "../../UI/Layout/TreeNode.h"
#include "../../UI/Widgets/InputField/InputText.h"
#include "../../UI/Layout/GroupCollapsable.h"
#include "../../Render/Resource/Loader/AnimLoader.h"
#include "../../Render/Animation/Animator.h"

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

	InitHierarchy();

	m_camera.SetPerspective(Deg2Rad(60.0f), 0.5, 0.1f, 5000.0f);
	m_actorPickRenderTarget = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, true);

	//std::filesystem::path pTest = "D:/Porject/LearnOpenGL-master/resources/objects/vampire/dancing_vampire.dae";
	//string realPath = std::filesystem::absolute(pTest).string();
	//m_curActor = &GLOBALSERVICE(EditorAction).CreateActorWithModel("Cube.fbx", false);
	//m_curActor->GetComponent< CMaterialRenderer>()->FillWithMaterial(*GLOBALSERVICE(MaterialManager)["Default.opmat"]);
	m_curActor = &GLOBALSERVICE(EditorAction).CreateActorWithModel("dancing_vampire.dae", false);
	m_curActor->GetComponent< CMaterialRenderer>()->FillWithMaterial(*GLOBALSERVICE(MaterialManager)["DefaultAnim.opmat"]);
	m_curActor->GetComponent<CTransform>()->SetLocalScale(Vector3(1000, 1000, 1000));

#if 0
	m_testAnim = AnimLoader::getInstance()->Create("dancing_vampire.dae", (EModelParserFlags)0x8);
	m_anim = new Animator(*m_curActor);
	m_anim->ReSetAnimation(*m_testAnim[0]);
#endif

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

	ImVec2 size(m_img->size);

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

#if 0
	m_anim->Update(deltaTime);

	Material* pMat =  m_curActor->GetComponent<CMaterialRenderer>()->GetMaterialList()[0];

	std::vector<Matrix4> data;
	for (int i = 0; i < 128; i++)
	{
		data.push_back(m_anim->GetFinalBoneMatrix()[i]);
	}

	pMat->SetMatrixArray("finalBonesMatrices[0]", data);
#endif
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


	m_renderTarget->Unbind();

}

void ModelView::InitHierarchy()
{
	//auto& it = m_img->CreateWidget<TreeNode>("testghjjjjjjjjjjjjjjjjj", true);
	//it.Open();
}
