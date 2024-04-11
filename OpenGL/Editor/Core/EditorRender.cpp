#include "EditorRender.h"
#include "Context.h"
#include <memory.h>
#include "../../Camera/Camera.h"
#include "../../Util/common.h"
#include "../../Scene/SceneManager.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../Core/ECS/Components/CLight.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"
#include "../../Render/ShapeDrawer.h"
#include "../../Editor/Core/EditorResource.h"
#include "../../Render/Mesh/Mesh.h"
#include "../../Render/Mesh/Model.h"
#include "../../Math/Math.h"
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
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilOperations(GL_KEEP, GL_KEEP, GL_REPLACE);//模板测试失败 模板通过深度失败 模板和深度都通过
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->SetStencilAlgorithm(GL_ALWAYS, 1, 0xff); //设置蒙板测试总是通过，参考值设为1，掩码值为x

	InitMaterials();

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->RegisterModelMatrixSender([this](Matrix4 mat4)
		{
			m_context.m_engineUBO->SetSubData(mat4, 0); // model
		});

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->RegisterUserMatrixSender([this](Matrix4 mat4)
		{
			m_context.m_engineUBO->SetSubData(mat4, 
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
	m_defaultMaterial.SetShader(m_context.shaderMgr["Standard.glsl"]);
	m_defaultMaterial.SetVector("u_Diffuse", Vector4(1.f, 1.f, 1.f, 1.f));
	m_defaultMaterial.SetFloat("u_Shininess", 100.0f);
	m_defaultMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);

	m_cameraMaterial.SetShader(m_context.shaderMgr["Lambert.glsl"]);
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

	m_outlineMaterial.SetShader(m_context.shaderMgr["Unlit.glsl"]);
	m_outlineMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);
	m_outlineMaterial.DepthTest = false;

	m_lightMaterial.SetShader(m_context.m_editorResource->GetShader("Billboard"));
	m_lightMaterial.SetVector("u_Diffuse", Vector4(1.f, 1.f, 0.5f, 0.5f));
	m_lightMaterial.Cull = false;
	m_lightMaterial.Blend = true;
	m_lightMaterial.DepthTest = false;

	m_stencilFillMaerial.SetShader(m_context.shaderMgr["Unlit.glsl"]);
	m_stencilFillMaerial.SetTexture("u_DiffuseMap", m_pTexture, 0);
	m_stencilFillMaerial.DepthTest = false;
	m_stencilFillMaerial.ColorWrite = false;
	m_stencilFillMaerial.DepthWrite = true;

	m_actorPickingMaterial.SetShader(m_context.shaderMgr["Unlit.glsl"]);
	m_actorPickingMaterial.SetVector("u_Diffuse", Vector4(1.f, 1.f, 1.f, 1.0f));
	m_actorPickingMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);

	m_emptyMaterial.SetShader(m_context.shaderMgr["Unlit.glsl"]);
	m_emptyMaterial.SetVector("u_Diffuse", Vector4(1.f, 0.f, 1.f, 1.0f));
	m_emptyMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);
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
	auto scale = Scale(actor.m_transform.GetWorldScale());
	Quaternion rotQuat = actor.m_transform.GetWorldRotation();
	Matrix4 rotation = rotQuat.ToMatrix4();

	return  translation * rotation * scale;
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

	Matrix4 model = Translate({ p_viewPos.x, 0.0f, p_viewPos.z }) * Scale({ gridSize * 2.0f, 1.f, gridSize * 2.0f });
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
		auto& actor = modelRender->owner;

		if (actor.IsActive())
		{
			PreparePickingMaterial(actor, m_actorPickingMaterial);
			auto model = modelRender->GetModel();
			auto modelMatrix = CalculateCameraModelMatrix(actor);

			dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(*model, m_actorPickingMaterial, &modelMatrix);
		}
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

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->Clear(false, true, false);

	m_lightMaterial.DepthTest = true;
	m_lightMaterial.SetFloat("u_Scale",  0.1f);
	m_lightMaterial.SetTexture("u_DiffuseMap", m_pTexture, 0);

	for (auto light : m_context.m_sceneMgr->GetActiveScene()->GetFastAccessComponents().lights)
	{
		auto& actor = light->owner;

		if (actor.IsActive())
		{
			PreparePickingMaterial(actor, m_lightMaterial);
			auto& model = *m_context.m_editorResource->GetModel("Vertical_Plane");
			auto modelMatrix = Translate(actor.m_transform.GetWorldPosition());
			dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(model, m_lightMaterial, &modelMatrix);
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
			
			if(p_isSelected)
				RenderCameraFrustum(*cameraComponent);
		}

	}

}

void EditorRender::RenderActor(Actor& p_actor)
{
	CModelRenderer* pRenderer = p_actor.GetComponent<CModelRenderer>();
	CMaterialRenderer* pMaterial = p_actor.GetComponent<CMaterialRenderer>();
	if (pRenderer || pMaterial)
	{
		Material pMat = m_context.materialMgr["Default.opmat"]->Copy();
		for (auto item : pRenderer->GetModel()->GetMeshes())
		{
			auto modelMatrix = CalculateCameraModelMatrix(p_actor);
			modelMatrix = Scale(Vector3(0.05f)) * modelMatrix;

			pMat.SetVector("u_Diffuse", Vector4(item->materialProperty.Diffuse.r, item->materialProperty.Diffuse.g, item->materialProperty.Diffuse.b, 1.0f));
			pMat.SetVector("u_Specular", Vector3(item->materialProperty.Specular.r, item->materialProperty.Specular.g, item->materialProperty.Specular.b));
			pMat.SetFloat("u_Shininess", item->materialProperty.Shininess);

			if (auto it = item->Textures.find("diffuse_0"); it != item->Textures.end())
			{
				pMat.SetTextureValue("u_DiffuseMap", item->Textures["diffuse_0"]);
			}

			if (auto it = item->Textures.find("specular_0"); it != item->Textures.end())
			{
				pMat.SetTextureValue("u_SpecularMap", item->Textures["specular_0"]);
			}

			if (auto it = item->Textures.find("normal_0"); it != item->Textures.end())
			{
				pMat.SetTextureValue("u_NormalMap", item->Textures["normal_0"]);
			}

			if (auto it = item->Textures.find("height_0"); it != item->Textures.end())
			{
				pMat.SetTextureValue("u_HeightMap", item->Textures["height_0"]);
			}
			
			pMaterial->FillWithMaterial(pMat);

			dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawMesh(*item, pMat, &modelMatrix);
		}


	}
}

void EditorRender::RenderLights()
{
	m_lightMaterial.SetFloat("u_Scale",  0.1f);

	for (auto light : m_context.m_sceneMgr.get()->GetActiveScene()->GetFastAccessComponents().lights)
	{
		auto& actor = light->owner;

		if (actor.IsActive())
		{
			auto model = m_context.m_editorResource->GetModel("Vertical_Plane");
			auto modelMatrix = Translate(actor.m_transform.GetWorldPosition());

			Texture* texture = nullptr;

			switch ((Light::Type)(int)light->GetData().type)
			{
			case Light::Type::Point: texture = m_context.m_editorResource->GetTexture("Icon_PointLight"); break;
			case Light::Type::Directional: texture = m_context.m_editorResource->GetTexture("Icon_DirectionlLight"); break;
			case Light::Type::Spot: texture = m_context.m_editorResource->GetTexture("Icon_SpotLight"); break;
			case Light::Type::Ambient_Box: texture = m_context.m_editorResource->GetTexture("Icon_SkyLight"); break;
			case Light::Type::Ambient_Sphere: texture = m_context.m_editorResource->GetTexture("Icon_SkyLight"); break;
			}

			const auto& lightColor = light->GetColor();
			m_lightMaterial.SetTexture("u_DiffuseMap", texture, texture->ID);
			m_lightMaterial.SetVector("u_Diffuse", Vector4(lightColor.r, lightColor.g, lightColor.b, 1.0f));
			dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(*model, m_lightMaterial, &modelMatrix);
		}
	}
}

void EditorRender::RenderCameraFrustum(CCamera& p_camera)
{
	auto gameViewSize = { 16, 9 };
	RenderCameraPerspectiveFrustum((std::pair<uint16_t, uint16_t>&)(gameViewSize), p_camera);
}

void EditorRender::RenderMaterialAsset(Material& p_material)
{
	Matrix4 model = Scale(glm::vec3(3.0f));
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->DrawModelWithSingleMaterial(*m_context.m_editorResource->GetModel("Sphere"), p_material, &model, &m_emptyMaterial);
}

void EditorRender::RenderCameraOrthographicFrustum(std::pair<uint16_t, uint16_t>& p_size, CCamera& p_camera)
{
	auto& owner = p_camera.owner;
	auto& camera = p_camera.GetCamera();
	const auto ratio = p_size.first / static_cast<float>(p_size.second);

	const auto& cameraPos = owner.m_transform.GetWorldPosition();
	const auto& cameraRotation = owner.m_transform.GetWorldRotation();
	const auto& cameraForward = (Quaternion)cameraRotation * Vector3(0.0f, 0.0f, 1.0f);

	const auto _near = camera.Near;
	const auto _far = camera.Far;
	const auto _size = p_camera.GetSize();

	const auto right = ratio * _size;
	const auto left = -right;
	const auto top = _size;
	const auto bottom = -top;

	const auto a = (Quaternion)cameraRotation * Vector3{ left, top, 0 };
	const auto b = (Quaternion)cameraRotation * Vector3{ right, top, 0 };
	const auto c = (Quaternion)cameraRotation * Vector3{ left, bottom, 0 };
	const auto d = (Quaternion)cameraRotation * Vector3{ right, bottom, 0 };

	DrawFrustumLines(*m_context.m_shapeDrawer, cameraPos, cameraForward, _near, _far, a, b, c, d, a, b, c, d);
}

void EditorRender::DebugRenderOrthographicFrustum(const Vector3& pos, const Vector3& forward, float nearPanel, const float farPanel, const Vector3& a,
	const Vector3& b, const Vector3& c, const Vector3& d)
{
	DrawFrustumLines(*m_context.m_shapeDrawer, pos, forward, nearPanel, farPanel, a, b, c, d, a, b, c, d);
}

void EditorRender::RenderCameraPerspectiveFrustum(std::pair<uint16_t, uint16_t> p_size, CCamera& p_camera)
{
	const auto& owner = p_camera.owner;
	auto& camera = p_camera.GetCamera();

	const auto& cameraPos = owner.m_transform.GetWorldPosition();
	const auto& cameraRotation = owner.m_transform.GetWorldRotation();
	const auto& cameraForward = (Quaternion)cameraRotation * Vector3(0.0f, 0.0f, 1.0f);

	camera.CalculateProjectMatrix(16, 9);
	camera.CalculateViewMatrix(cameraPos, cameraRotation);
	const auto proj = glm::transpose(camera.Projection);
	const auto nearPanel = camera.Near;
	const auto farPanel = camera.Far;

	const auto nLeft = nearPanel * (proj[0][2] - 1.0f) / proj[0][0];
	const auto nRight = nearPanel * (1.0f + proj[0][2]) / proj[0][0];
	const auto nTop = nearPanel * (1.0f + proj[1][2]) / proj[1][1];
	const auto nBottom = nearPanel * (proj[1][2] - 1.0f) / proj[1][1];

	const auto fLeft = farPanel * (proj[0][2] - 1.0f) / proj[0][0];
	const auto fRight = farPanel * (1.0f + proj[0][2]) / proj[0][0];
	const auto fTop = farPanel * (1.0f + proj[1][2]) / proj[1][1];
	const auto fBottom = farPanel * (proj[1][2] - 1.0f) / proj[1][1];

	auto a = (Quaternion)cameraRotation * Vector3{ nLeft, nTop, 0 };
	auto b = (Quaternion)cameraRotation * Vector3{ nRight, nTop, 0 };
	auto c = (Quaternion)cameraRotation * Vector3{ nLeft, nBottom, 0 };
	auto d = (Quaternion)cameraRotation * Vector3{ nRight, nBottom, 0 };
	auto e = (Quaternion)cameraRotation * Vector3{ fLeft, fTop, 0 };
	auto f = (Quaternion)cameraRotation * Vector3{ fRight, fTop, 0 };
	auto g = (Quaternion)cameraRotation * Vector3{ fLeft, fBottom, 0 };
	auto h = (Quaternion)cameraRotation * Vector3{ fRight, fBottom, 0 };

	DrawFrustumLines(*m_context.m_shapeDrawer, cameraPos, cameraForward, nearPanel, farPanel, a, b, c, d, e, f, g, h);
}

void EditorRender::DrawFrustumLines(ShapeDrawer& p_drawer, const Vector3& pos, const Vector3& forward, float nearPanel, const float farPanel, const Vector3& a,
	const Vector3& b, const Vector3& c, const Vector3& d, const Vector3& e, const Vector3& f, const Vector3& g, const Vector3& h)
{
	// Convenient lambda to draw a frustum line
	auto draw = [&](const Vector3& p_start, const Vector3& p_end, const float planeDistance)
	{
		auto offset = pos + forward * planeDistance;
		auto start = offset + p_start;
		auto end = offset + p_end;
		p_drawer.DrawLine(start, end, Color3(1.0f, 1.0f, 1.0f));
	};

	// Draw near plane
	draw(a, b, nearPanel);
	draw(b, d, nearPanel);
	draw(d, c, nearPanel);
	draw(c, a, nearPanel);

	// Draw far plane
	draw(e, f, farPanel);
	draw(f, h, farPanel);
	draw(h, g, farPanel);
	draw(g, e, farPanel);

	// Draw lines between near and far planes
	draw(a + forward * nearPanel, e + forward * farPanel, 0);
	draw(b + forward * nearPanel, f + forward * farPanel, 0);
	draw(c + forward * nearPanel, g + forward * farPanel, 0);
	draw(d + forward * nearPanel, h + forward * farPanel, 0);
}

void EditorRender::RenderGizmo(Vector3& p_pos, Quaternion& p_quat, EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis) //绘制gizmo
{
	// OpenGL T * R * S
	//DirectX S * R * T

	Matrix4 model = Translate(p_pos) * p_quat.ToMatrix4();

	Model* arrowModel = nullptr;

	if (!p_pickable)
	{
		Matrix4 sphereModel = model * Scale(Vector3(0.1f, 0.1f, 0.1f));

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