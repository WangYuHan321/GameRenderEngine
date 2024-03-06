#include "ForwardRenderer.h"
#include "RenderTarget.h"

#include "../Camera/FlyCamera.h"
#include "../Render/Mesh/Mesh.h"
#include "../Render/Mesh/Material.h"
#include "../Scene/Scene.h"
#include "../../Core/ECS/Actor.h"
#include "../../Render/Mesh/Model.h"
#include "../Core/ECS/Components/CModelRenderer.h"
#include "../Core/ECS/Components/CMaterialRenderer.h"

ForwardRenderer::ForwardRenderer():
	m_state(0)
{
}

ForwardRenderer::~ForwardRenderer()
{
}

void ForwardRenderer::DoRender()
{
	this->Clear(true, true, true);
}

void ForwardRenderer::OnReSize(uint32 width, uint32 height)
{
	m_renderTarget->Resize(width, height);
}

void ForwardRenderer::SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height)
{
	if (width <= 0 || height <= 0)
		return;
	glViewport(x, y, width, height);
}

void ForwardRenderer::Initialize()
{
	m_renderTarget = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 1, true);
}

void ForwardRenderer::SetRasterizationModel(GLenum model)
{
	glPolygonMode(GL_FRONT_AND_BACK, model);
}

void ForwardRenderer::SetRasterizationLineWidth(float p_lineWidth)
{
	glLineWidth(p_lineWidth);
}

void ForwardRenderer::SetCapability(GLenum model, bool p_value)
{
	(p_value ? glEnable : glDisable)(model);
}

void ForwardRenderer::SetStencilOperations(GLenum operation, GLenum depthFail, GLenum bothPass)
{
	glStencilOp(static_cast<GLenum>(operation), static_cast<GLenum>(depthFail), static_cast<GLenum>(bothPass));
}

void ForwardRenderer::SetStencilAlgorithm(GLenum operation, int32_t value, uint32_t mask)
{
	glStencilFunc(static_cast<GLenum>(operation), value, mask);
}

void ForwardRenderer::SetStencilMask(uint32_t p_mask)
{
	glStencilMask(p_mask);
}

void ForwardRenderer::RenderScene(Scene& p_scene,
	const Vector3& p_cameraPosition,
	const Camera& p_camera,
	const Frustum* p_customFrustum,
	Material* p_defaultMaterial)
{
	OpaqueDrawables	opaqueMeshes;
	TransparentDrawables transparentMeshes;

	std::tie(opaqueMeshes, transparentMeshes) = FindAndSortDRawables(p_scene, p_cameraPosition, p_defaultMaterial);

	for (const auto& [distance, drawable] : opaqueMeshes)
		DrawDrawable(drawable);

	for (const auto& [distance, drawable] : transparentMeshes)
		DrawDrawable(drawable);

}

std::pair<ForwardRenderer::OpaqueDrawables, ForwardRenderer::TransparentDrawables> ForwardRenderer::FindAndSortDRawables(const Scene& p_scene, const Vector3 p_camPos, Material* p_defaultMaterial)
{
	ForwardRenderer::OpaqueDrawables opaqueDrawables;
	ForwardRenderer::TransparentDrawables transparentDrawables;

	for (auto modelRender : p_scene.GetFastAccessComponents().modelRenderers)
	{
		if (modelRender->owner.IsActive())
		{
			if (auto model = modelRender->GetModel())
			{
				//离相机距离
				float distanceToActor = glm::distance(modelRender->owner.m_transform.GetWorldPosition(), p_camPos);

				if (auto materialRender = modelRender->owner.GetComponent<CMaterialRenderer>())
				{
					auto& transform = modelRender->owner.m_transform.GetFTransform();

					CMaterialRenderer::MaterialList materialList = materialRender->GetMaterialList();

					for (auto mesh : model->m_meshes)
					{
						Material* materialPtr = nullptr;
						if (mesh->MaterialIndex < MAX_MATERIAL_COUNT)
						{
							materialPtr = materialList.at(mesh->MaterialIndex);
							if (!materialPtr || !materialPtr->GetShader())
							{
								//如果没有就用默认的shader
								materialPtr = p_defaultMaterial;
							}
						}

						if (materialPtr)
						{
							Drawable element = { transform.GetWorldMatrix(), mesh, materialPtr, materialRender->GetUserMatrix() };

							if (materialPtr->Blend)
								transparentDrawables.emplace(distanceToActor, element);
							else
								opaqueDrawables.emplace(distanceToActor, element);
						}

					}

				}
			}

		}
	}
	return { opaqueDrawables, transparentDrawables };
}

void ForwardRenderer::DrawDrawable(const Drawable& p_toDraw)
{
	m_userMatrixSender(std::get<3>(p_toDraw));
	DrawMesh(*std::get<1>(p_toDraw), *std::get<2>(p_toDraw), (Matrix4*)&std::get<0>(p_toDraw));
}

void ForwardRenderer::DrawModelWithSingleMaterial(Model& p_model, Material& p_material, Matrix4* p_modelMat, Material* p_defaultMaterial)
{
	if (p_modelMat)
		m_modelMatrixSender(*p_modelMat);

	for(auto mesh : p_model.GetMeshes())
	{
		Material* material = p_material.GetShader() ? &p_material : p_defaultMaterial;

		if (material)
			DrawMesh(*mesh, *material, nullptr);
	}

}

void ForwardRenderer::DrawMesh(Mesh& p_mesh, Material& p_material, Matrix4* p_mat4)
{
	if (p_material.GetShader() && p_material.GPUInstance > 0)
	{
		if(p_mat4)
			m_modelMatrixSender(*p_mat4);

		uint8_t stateMask = p_material.GenerateStateMask();
		ApplyStateMask(stateMask);

		/* Draw the mesh */
		p_material.Bind();
		Draw(p_mesh, EPrimitiveMode::TRIANGLES, p_material.GPUInstance);
		p_material.UnBind();
	}
}

void ForwardRenderer::Draw(Mesh& p_mesh, EPrimitiveMode model, uint32 drawNumObj)
{
	if (drawNumObj > 0)
	{
		++m_frameInfo.batchCount;
		m_frameInfo.instanceCount += drawNumObj;
		m_frameInfo.polyCount += (p_mesh.Indices.size() / 3) * drawNumObj;

		p_mesh.Bind();

		if (p_mesh.Indices.size() > 0)
		{
			if (drawNumObj == 1)
				glDrawElements(static_cast<GLenum>(model), p_mesh.Indices.size(), GL_UNSIGNED_INT, nullptr);
			else
				glDrawElementsInstanced(static_cast<GLenum>(model), p_mesh.Indices.size(), GL_UNSIGNED_INT, nullptr, drawNumObj);
		}
		else
		{
			if (drawNumObj == 1)
				glDrawArrays(static_cast<GLenum>(model), 0, p_mesh.Positions.size());
			else
				glDrawArraysInstanced(static_cast<GLenum>(model), 0, p_mesh.Positions.size(), drawNumObj);
		}
		p_mesh.UnBind();
	}
}

void ForwardRenderer::ApplyStateMask(uint8_t p_mask)
{
	//if (m_state != p_mask)
	//{

		if ((p_mask & 0x01) != (m_state & 0x01))    m_glCache.SetDepthMask(p_mask & 0x01);
		if ((p_mask & 0x02) != (m_state & 0x02))	m_glCache.SetColorMask(p_mask & 0x02);
		if ((p_mask & 0x04) != (m_state & 0x04))	m_glCache.SetBlend( p_mask & 0x04);
		if ((p_mask & 0x08) != (m_state & 0x08))	m_glCache.SetCull(p_mask & 0x08);
		if ((p_mask & 0x10) != (m_state & 0x10))	m_glCache.SetDepthTest(p_mask & 0x10);

		m_glCache.SetCullFace((p_mask & 0x20) ? GL_BACK : GL_FRONT);

		m_state = p_mask;
	//}
}

uint8_t ForwardRenderer::FetchGLState()
{

	return m_state;
}

void ForwardRenderer::SetState(uint8_t p_state)
{
	m_state = p_state;
}

void ForwardRenderer::RegisterModelMatrixSender(std::function<void(Matrix4)> p_modelMatrixSender)
{
	m_modelMatrixSender = p_modelMatrixSender;
}

void ForwardRenderer::RegisterUserMatrixSender(std::function<void(Matrix4)> p_userMatrixSender)
{
	m_userMatrixSender = p_userMatrixSender;
}

void ForwardRenderer::ReadPixels(uint32_t x, uint32_t y, uint32_t width, uint32_t height, GLenum format, GLenum type, void* data)
{
	glReadPixels(x, y, width, height, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
}

void ForwardRenderer::Clear(bool p_colorBuffer, bool p_deptBuffer, bool p_stencilColor)
{
	glClear((p_colorBuffer ? GL_COLOR_BUFFER_BIT : 0) |
		(p_deptBuffer ? GL_DEPTH_BUFFER_BIT : 0) |
		(p_stencilColor ? GL_STENCIL_BUFFER_BIT : 0) 
	);
}
