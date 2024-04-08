#include "ForwardRenderer.h"
#include "RenderTarget.h"
#include "../Scene/Scene.h"
#include "../Camera/FlyCamera.h"
#include "../Render/Mesh/Mesh.h"
#include "../../Core/ECS/Actor.h"
#include "../../Render/Mesh/Model.h"
#include "../Render/Mesh/Material.h"
#include "../Global/ServiceLocator.h"
#include "../../Render/Mesh/Material.h"
#include "../Core/ECS/Components/CLight.h"
#include "../../Render/Resource/RawShader.h"
#include "../Render/Shadow/CascadeShadowMap.h"
#include "../Core/ECS/Components/CModelRenderer.h"
#include "../Core/ECS/Components/CDirectionalLight.h"
#include "../Core/ECS/Components/CMaterialRenderer.h"
#include "../../Render/Resource/Loader/ShaderLoader.h"

ForwardRenderer::ForwardRenderer()
{
	m_pShadowMaterial = new Material();
	auto shadowSource = RawShader::GetShadow();
	m_pShader = ShaderLoader::getInstance()->CreateFromSource("Shadow Shader", shadowSource.first, shadowSource.second);
	m_pShadowMaterial->SetShader(m_pShader);
}

ForwardRenderer::~ForwardRenderer()
{
	if (m_pShadowMaterial)
		delete m_pShadowMaterial;

	if (m_pShader)
		delete m_pShader;
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

	GLOBALSERVICE(CascadeShadowMap).Clear();
	for (const auto& [distance, drawable] : opaqueMeshes)
		DrawDrawableShadow(p_scene, drawable, p_camera);

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
	if (std::get<2>(p_toDraw)->ShadowReceive)
		GLOBALSERVICE(CascadeShadowMap).SetShadowMap(std::get<2>(p_toDraw));
	DrawMesh(*std::get<1>(p_toDraw), *std::get<2>(p_toDraw), (Matrix4*)&std::get<0>(p_toDraw));
}

void ForwardRenderer::DrawDrawableShadow(const Scene& p_scene, const Drawable& p_toDraw, const Camera& p_camera)
{
	for (auto dirLight : p_scene.GetFastAccessComponents().lights)
	{
		if (dirLight->GetData().type == float(Light::Type::Directional))
		{
			GLOBALSERVICE(CascadeShadowMap).InitializeFrame(*static_cast<CDirectionalLight*>(dirLight), &p_camera);
			if (std::get<2>(p_toDraw)->ShadowCast)
			{
				glDisable(GL_STENCIL_TEST);
				for (unsigned int i = 0; i < 2; i++)
				{
					GLOBALSERVICE(CascadeShadowMap).BeginShadowRender(i);
					m_userMatrixSender(GLOBALSERVICE(CascadeShadowMap).GetCurDepthMatrix4());
					
					if(std::get<2>(p_toDraw)->ShadowCast)
						DrawMesh(*std::get<1>(p_toDraw), *m_pShadowMaterial, (Matrix4*)&std::get<0>(p_toDraw));
				}
				
				GLOBALSERVICE(CascadeShadowMap).EndShadowRender();
				glEnable(GL_STENCIL_TEST);
			}
		}
	}

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
		
		m_glCache.ApplyMaterial(p_material);

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

void ForwardRenderer::SetClearColor(float p_red, float p_green, float p_blue, float p_alpha)
{
	glClearColor(p_red, p_green, p_blue, p_alpha);
}

void ForwardRenderer::Clear(Camera& camera, bool p_colorBuffer, bool p_depthBuffer, bool p_stencilBuffer)
{
	GLfloat previousClearColor[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, previousClearColor);

	Color4 cameraClearColor = camera.ClearColor;
	SetClearColor(cameraClearColor.r, cameraClearColor.g, cameraClearColor.b, 1.0f);
	Clear(p_colorBuffer, p_depthBuffer, p_stencilBuffer);

	SetClearColor(previousClearColor[0], previousClearColor[1], previousClearColor[2], previousClearColor[3]);
}

void ForwardRenderer::Clear(bool p_colorBuffer, bool p_deptBuffer, bool p_stencilColor)
{
	glClear((p_colorBuffer ? GL_COLOR_BUFFER_BIT : 0) |
		(p_deptBuffer ? GL_DEPTH_BUFFER_BIT : 0) |
		(p_stencilColor ? GL_STENCIL_BUFFER_BIT : 0)
	);
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

std::vector<Matrix4> ForwardRenderer::GetFindLightMatrices(const Scene& p_scene)
{
	std::vector<Matrix4> result;

	for (auto light : p_scene.GetFastAccessComponents().lights)
	{
		if (light->owner.IsActive())
		{
			result.push_back(light->GetData().GenerateMatrix());
		}
	}
	return result;
}


