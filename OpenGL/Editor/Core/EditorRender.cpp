#include "EditorRender.h"
#include "Context.h"
#include <memory.h>
#include "../../Camera/Camera.h"
#include "../../Util/common.h"
#include "../../Scene/SceneManager.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
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
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);//模板测试 深度测试 模和深都成功

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetCapability(GL_STENCIL_TEST, true);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilOperations(GL_KEEP, GL_REPLACE, GL_REPLACE);//模板测试失败 模板通过深度失败 模板和深度都通过
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilAlgorithm(GL_ALWAYS, 1, 0xff); //设置蒙板测试总是通过，参考值设为1，掩码值为x

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
	m_defaultMaterial.SetShader(m_context.shaderMgr["Standard"]);
	m_defaultMaterial.SetVector("u_Diffuse", Vector4(1.f, 1.f, 1.f, 1.f));
	m_defaultMaterial.SetFloat("u_Shininess", 100.0f);
	m_defaultMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);

	m_cameraMaterial.SetShader(m_context.shaderMgr["Lambert"]);
	m_cameraMaterial.SetVector("u_Diffuse", glm::vec4(0.0f, 0.3f, 0.7f, 1.0f));
	m_cameraMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);

	m_gridMaterial.SetShader(m_context.m_editorResource->GetShader("Grid"));
	m_gridMaterial.Blend = true;
	m_gridMaterial.Cull = false;
	m_gridMaterial.DepthTest = false;

	m_gizmoArrowMaterial.SetShader(m_context.m_editorResource->GetShader("Gizmo"));
	m_gizmoArrowMaterial.GPUInstance = 3;
	m_gizmoArrowMaterial.SetBoolean("u_IsBall", false);
	m_gizmoArrowMaterial.SetBoolean("u_IsPickable", false);

	m_gizmoBallMaterial.SetShader(m_context.m_editorResource->GetShader("Gizmo"));
	m_gizmoBallMaterial.SetBoolean("u_IsBall", true);
	m_gizmoBallMaterial.SetBoolean("u_IsPickable", false);

	m_gizmoPickingMaterial.SetShader(m_context.m_editorResource->GetShader("Gizmo"));
	m_gizmoPickingMaterial.GPUInstance = 3;
	m_gizmoPickingMaterial.SetBoolean("u_IsBall", false);
	m_gizmoPickingMaterial.SetBoolean("u_IsPickable", true);

	m_outlineMaterial.SetShader(m_context.shaderMgr["Unlit"]);
	m_outlineMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);
	m_outlineMaterial.DepthTest = false;

	m_stencilFillMaerial.SetShader(m_context.shaderMgr["Unlit"]);
	m_stencilFillMaerial.SetTexture("u_DiffuseMap", m_pTexture, 0);
	m_stencilFillMaerial.DepthTest = false;
	m_stencilFillMaerial.ColorWrite = false;
	m_stencilFillMaerial.DepthWrite = true;

	m_actorPickingMaterial.SetShader(m_context.shaderMgr["Unlit"]);
	m_actorPickingMaterial.SetVector("u_Diffuse", Vector4(1.f, 1.f, 1.f, 1.0f));
	m_actorPickingMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);
}

void EditorRender::PreparePickingMaterial(Actor& p_actor, Material& p_material)
{
	uint32_t actorID = static_cast<uint32_t>(p_actor.GetID());

	auto bytes = reinterpret_cast<uint8_t*>(&actorID);
	auto color = Color4( bytes[0] / 255.0f, bytes[1] / 255.0f, bytes[2] / 255.0f, 1.0f );

	p_material.SetVector("u_Diffuse", Vector4(color.r, color.g, color.b, color.a));
}

Matrix4 EditorRender::CalculateCameraModelMatrix(Actor& actor)
{
	auto translation = Translate(actor.m_transform.GetWorldPosition());
	Quaternion rotQuat = actor.m_transform.GetWorldRotation();
	Matrix4 rotation = rotQuat.ToMatrix4();

#if 0
	printf(" --------------------------------------------------------- \n");
	Matrix4 mattt = translation;

	printf(" %s \n", glm::to_string(mattt).c_str());

	mattt = rotation;

	printf(" %s \n", glm::to_string(mattt).c_str());

	mattt = rotation * translation;

	printf(" %s \n", glm::to_string(mattt).c_str());

	printf(" --------------------------------------------------------- \n");

#endif

	return  rotation * translation;
}

void EditorRender::UpdateLights(Scene& p_scene)
{
	auto lightMatrices = dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->GetFindLightMatrices(p_scene);
	m_context.m_lightSSBO->SetSubData<Matrix4>(lightMatrices.data(), lightMatrices.size() * sizeof(Matrix4));
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

	for (auto camera : m_context.m_sceneMgr->GetActiveScene()->GetFastAccessComponents().cameras)
	{
		auto& actor = camera->owner;

		if (actor.IsActive())
		{
			PreparePickingMaterial(actor, m_actorPickingMaterial);
			auto& model = *m_context.m_editorResource->GetModel("Camera");
			auto modelMatrix = CalculateCameraModelMatrix(actor);

			dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(model, m_actorPickingMaterial, &modelMatrix);
		}
	}
}

void EditorRender::RenderModelToStencil(Matrix4& p_worldMatrix, Model& p_model)
{
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilMask(0xFF);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(p_model, m_stencilFillMaerial, &p_worldMatrix);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilMask(0x00);
}

void EditorRender::RenderModelOutline(Matrix4& p_worldMatrix, Model& p_model, float p_width)
{
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilAlgorithm(GL_NOTEQUAL, 1, 0xFF);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetRasterizationModel(GL_LINE);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetRasterizationLineWidth(p_width);
	
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(p_model, m_outlineMaterial, &p_worldMatrix);

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetRasterizationLineWidth(1.f);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetRasterizationModel(GL_FILL);
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilAlgorithm(GL_ALWAYS, 1, 0xFF);
}

void EditorRender::RenderActorOutlinePass(Actor& p_actor, bool p_toStencil, bool p_isSelected)
{
	float outlineWidth = p_isSelected ? 5.0f : 2.5f;

	m_outlineMaterial.SetVector("u_Diffuse", p_isSelected ? Vector4(1.f, 0.7f, 0.f, 1.0f) : Vector4(1.f, 1.f, 0.f, 1.0f));

	if (p_actor.IsActive())
	{
		if (auto modelRenderer = p_actor.GetComponent<CModelRenderer>(); modelRenderer)
		{
			if (p_toStencil)
				RenderModelToStencil((Matrix4&)p_actor.m_transform.GetWorldMatrix(), *modelRenderer->GetModel());
			else
				RenderModelOutline((Matrix4&)p_actor.m_transform.GetWorldMatrix(), *modelRenderer->GetModel(), outlineWidth);
		}

		if (auto cameraComponent = p_actor.GetComponent<CCamera>(); cameraComponent)
		{
			auto model = CalculateCameraModelMatrix(p_actor);

			if (p_toStencil)
				RenderModelToStencil(model, *m_context.m_editorResource->GetModel("Camera"));
			else
				RenderModelOutline(model, *m_context.m_editorResource->GetModel("Camera"), outlineWidth);
		}

	}

}

void EditorRender::RenderGizmo(Vector3& p_pos, Quaternion& p_quat, EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis) //绘制gizmo
{

	Matrix4 model = p_quat.Normalize().ToMatrix4() * Translate(p_pos);

	Model* arrowModel = nullptr;

	if (!p_pickable)
	{
		Matrix4 sphereModel = Scale(Vector3(0.1f, 0.1f, 0.1f)) * model;

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
		dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(*arrowModel, p_pickable ? m_gizmoPickingMaterial : m_gizmoArrowMaterial, &model);
	}
}