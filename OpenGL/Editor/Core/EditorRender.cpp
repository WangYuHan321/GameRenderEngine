#include "EditorRender.h"
#include "Context.h"
#include <memory.h>
#include "../../Camera/Camera.h"
#include "../../Util/common.h"
#include "../../Scene/SceneManager.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../Editor/Core/EditorResource.h"
#include "../../Render/Mesh/Mesh.h"
#include "../../Render/Mesh/Model.h"
#include "../../Render/Resource/Loader/TextureLoader.h"
#include <glm/gtx/string_cast.hpp>


EditorRender::EditorRender(Context& p_context):
	m_context(p_context),
	m_pTexture(TextureLoader::getInstance()->CreateColor(
		(255 << 24) | (255 << 16) | (255 << 8) | 255,
		GL_NEAREST,
		GL_NEAREST,
		false
	))
{

	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);//ģ����� ��Ȳ��� ģ����ɹ�

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetCapability(GL_STENCIL_TEST, true);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilOperations(GL_KEEP, GL_REPLACE, GL_REPLACE);//ģ�����ʧ�� ģ��ͨ�����ʧ�� ģ�����ȶ�ͨ��
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilAlgorithm(GL_ALWAYS, 1, 0xff); //�����ɰ��������ͨ�����ο�ֵ��Ϊ1������ֵΪx

	InitMaterials();

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->RegisterModelMatrixSender([this](Matrix4 mat4)
		{
			m_context.m_engineUBO->SetSubData(glm::transpose(mat4), 0); // model
		});

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->RegisterUserMatrixSender([this](Matrix4 mat4)
		{
			m_context.m_engineUBO->SetSubData(glm::transpose(mat4), 
				sizeof(Matrix4) +
				sizeof(Matrix4) +
				sizeof(Matrix4) +
				sizeof(Vector3) +
				sizeof(float)
				);
		});

}

EditorRender::~EditorRender()
{
	TextureLoader::getInstance()->Destroy(m_pTexture);
}

void EditorRender::InitMaterials()
{
	m_cameraMaterial.SetShader(m_context.shaderMgr["Lambert"]);
	m_cameraMaterial.SetVector("u_Diffuse", glm::vec4(0.0f, 0.3f, 0.7f, 1.0f));
	m_cameraMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);

	m_gridMaterial.SetShader(m_context.m_editorResource->GetShader("Grid"));
	m_gridMaterial.Blend = true;
	m_gridMaterial.Cull = false;
	m_gridMaterial.DepthTest = false;
}

Matrix4 EditorRender::CalculateCameraModelMatrix(Actor& actor)
{
	auto translation = Translate(actor.m_transform.GetWorldPosition());
	Quaternion rotQuat = actor.m_transform.GetWorldRotation();
	Matrix4 rotation = rotQuat.ToMatrix4();

#if 0
	//Matrix4 mattt = translation;

	//printf(" %s \n", glm::to_string(mattt).c_str());

	//mattt = rotation;

	//printf(" %s \n", glm::to_string(mattt).c_str());

	//mattt = rotation * translation;

	//printf(" %s \n", glm::to_string(mattt).c_str());

	//mattt = glm::transpose(rotation * translation);

	//printf(" %s \n", glm::to_string(mattt).c_str());

#endif

	return  rotation * translation;
}

void EditorRender::DoRender()
{
	
}

void EditorRender::RenderCameras()
{
	for (auto camera : m_context.m_sceneMgr.get()->GetActiveScene()->GetFastAccessComponents().cameras)
	{
		auto& actor = camera->owner;

		if (actor.IsActive())
		{
			auto& model = *m_context.m_editorResource->GetModel("Camera");
			auto modelMatrix = CalculateCameraModelMatrix(actor);
			dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(model, m_cameraMaterial, &modelMatrix);
		}
	}
}

void EditorRender::RenderScene(const Vector3& p_cameraPos, const Camera& p_camera)
{
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->RenderScene(*m_context.m_sceneMgr->GetActiveScene(), p_cameraPos, p_camera, nullptr, &m_emptyMaterial);
}

void EditorRender::RenderUI()
{
	m_context.m_uiMgr->Render();
}

void EditorRender::RenderGrid(Vector3& p_viewPos, Vector3& p_color)
{
	constexpr float gridSize = 5000.0f;

	Matrix4 model = Scale({ gridSize * 2.0f, 1.f, gridSize * 2.0f }) * Translate({ p_viewPos.x, 0.0f, p_viewPos.z });
	m_gridMaterial.SetVector("u_Color", p_color);
	
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(*m_context.m_editorResource->GetModel("Plane"), m_gridMaterial, &model);

	m_context.m_shapeDrawer->DrawLine(Vector3(-gridSize + p_viewPos.x, 0.0f, 0.0f), Vector3(gridSize + p_viewPos.x, 0.0f, 0.0f), Color3(1.0f, 0.0f, 0.0f), 1.0f);
	m_context.m_shapeDrawer->DrawLine(Vector3(0.0f, -gridSize + p_viewPos.y, 0.0f), Vector3(0.0f, gridSize + p_viewPos.y, 0.0f), Color3(0.0f, 1.0f, 0.0f), 1.0f);
	m_context.m_shapeDrawer->DrawLine(Vector3(0.0f, 0.0f, -gridSize + p_viewPos.z), Vector3(0.0f, 0.0f, gridSize + p_viewPos.z), Color3(0.0f, 0.0f, 1.0f), 1.0f);
}

void EditorRender::RenderSceneForActorPicking()
{
	auto& scene = *m_context.m_sceneMgr->GetActiveScene();

	for (auto modelRender : scene.GetFastAccessComponents().modelRenderers)
	{
	}

}

void EditorRender::RenderGizmo(Vector3& p_pos, Quaternion& p_quat, EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis)
{

	Matrix4 mat4 = p_quat.Normalize().ToMatrix4() * Translate(p_pos);

	Model* arrowModel = nullptr;

	if (!p_pickable)
	{
		Matrix4 sphereModel = Scale(Vector3(0.1f)) * mat4;

		dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(*m_context.m_editorResource->GetModel("Sphere"), m_gizmoBallMaterial, &sphereModel);
		m_gizmoArrowMaterial.SetInt("u_HighlightedAxis", p_highlightedAxis);

		switch (p_operation)
		{
		case EGizmoOperation::TRANSLATE:
			arrowModel = m_context.m_editorResource->GetModel("Arrow_Translate");
			break;
		case EGizmoOperation::ROTATE:
			arrowModel = m_context.m_editorResource->GetModel("Arrow_Rotate");
			break;
		case EGizmoOperation::SCALE:
			arrowModel = m_context.m_editorResource->GetModel("Arrow_Scale");
			break;
		}
	}
	else
	{
		arrowModel = m_context.m_editorResource->GetModel("Arrow_Picking");
	}

	if (arrowModel)
	{
		dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(*arrowModel, p_pickable ? m_gizmoPickingMaterial : m_gizmoArrowMaterial, &mat4);
	}
}