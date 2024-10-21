#include "DeferredRenderer.h"

#include "../../Util/common.h"
#include "../RenderTarget.h"
#include "../../Scene/Scene.h"
#include "../Mesh/Mesh.h"
#include "../Mesh/Material.h"
#include "../../Core/ECS/Actor.h"
#include "../Resource/Loader/ShaderLoader.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"

DeferredRenderer::DeferredRenderer()
{
	Initialize();
}

DeferredRenderer::~DeferredRenderer()
{
	delete m_renderGBuffer;
}

void DeferredRenderer::Initialize()
{
	m_renderGBuffer = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 6, true);
	for (int i = 0; i < 6; i++)
	{
		m_gBufferInfo = m_renderGBuffer->GetColorTexture(i);
	}
	m_gBufferDepth = m_renderGBuffer->GetDepthStencilTexture();

	m_gBufferShader = ShaderLoader::getInstance()->Create("Deferred/GBuffer.glsl");
}

void DeferredRenderer::DoRender()
{



}

void DeferredRenderer::OnReSize(uint32 width, uint32 height)
{
	m_renderGBuffer->Resize(width, height);
}

void DeferredRenderer::RenderScene(Scene& pScene, Camera& pCamera, Vector3& pCameraPos, Material* pDefaultMat)
{
	OpaqueDrawables opaqueMeshes;
	TransparentDrawables transparentMeshes;
	std::tie(opaqueMeshes, transparentMeshes) = FindAndSortDRawables(pScene, pCameraPos, pDefaultMat);

	glBindFramebuffer(GL_FRAMEBUFFER, m_renderGBuffer->ID);

	m_gBufferShader->ActiveShader();

	for (const auto& [distance, drawable] : opaqueMeshes)
		DrawDrawable(drawable);


}

std::pair<DeferredRenderer::OpaqueDrawables, DeferredRenderer::TransparentDrawables> DeferredRenderer::FindAndSortDRawables(const Scene& p_scene, const Vector3 p_camPos, Material* p_defaultMaterial)
{
	DeferredRenderer::OpaqueDrawables opaqueDrawables;
	DeferredRenderer::TransparentDrawables transparentDrawables;

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
						if (mesh->m_materialIndex < MAX_MATERIAL_COUNT)
						{
							materialPtr = materialList.at(mesh->m_materialIndex);
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

void DeferredRenderer::DrawDrawable(const Drawable& p_toDraw)
{
	Draw(*std::get<1>(p_toDraw), 1);
}

void DeferredRenderer::Draw(Mesh& p_mesh, uint32 drawNumObj)
{
	if (drawNumObj > 0)
	{

		p_mesh.Bind();

		if (p_mesh.m_vecIndices.size() > 0)
		{
			if (drawNumObj == 1)
				glDrawElements(static_cast<GLenum>(GL_TRIANGLES), p_mesh.m_vecIndices.size(), GL_UNSIGNED_INT, nullptr);
			else
				glDrawElementsInstanced(static_cast<GLenum>(GL_TRIANGLES), p_mesh.m_vecIndices.size(), GL_UNSIGNED_INT, nullptr, drawNumObj);
		}
		else
		{
			if (drawNumObj == 1)
				glDrawArrays(static_cast<GLenum>(GL_TRIANGLES), 0, p_mesh.m_vecPos.size());
			else
				glDrawArraysInstanced(static_cast<GLenum>(GL_TRIANGLES), 0, p_mesh.m_vecPos.size(), drawNumObj);
		}
		p_mesh.UnBind();
	}
}