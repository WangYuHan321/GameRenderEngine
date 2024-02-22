#include "EditorRender.h"
#include "Context.h"
#include <memory.h>
#include "../../Camera/Camera.h"
#include "../../Scene/SceneManager.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../Editor/Core/EditorResource.h"
#include "../../Render/Resource/Loader/TextureLoader.h"


EditorRender::EditorRender(Context& p_context):
	m_context(p_context),
	m_pTexture(TextureLoader::getInstance()->CreateColor(
		(255 << 24) | (255 << 16) | (255 << 8) | 255,
		GL_NEAREST,
		GL_NEAREST,
		false
	))
{
	InitMaterials();

	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->RegisterModelMatrixSender([this](Matrix4 mat4)
		{
			m_context.m_engineUBO->SetSubData(glm::transpose(mat4), 0);
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

}

Matrix4 EditorRender::CalculateCameraModelMatrix(Actor& actor)
{
	auto translation = Translate(actor.m_transform.GetWorldPosition());
	glm::mat4 rotation = glm::mat4_cast(actor.m_transform.GetWorldRotation());

	return  translation * rotation;
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