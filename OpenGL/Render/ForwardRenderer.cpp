#include "ForwardRenderer.h"
#include "RenderTarget.h"

#include "../Camera/FlyCamera.h"
#include "../Render/Mesh/Mesh.h"
#include "../Render/Mesh/Material.h"
#include "../Scene/Scene.h"
#include "../../Core/ECS/Actor.h"
#include "../Core/ECS/Components/CModelRenderer.h"
#include "../Core/ECS/Components/CMaterialRenderer.h"

void ForwardRenderer::DoRender()
{
	this->Clear(true, true, true);
}

void ForwardRenderer::OnReSize(uint32 width, uint32 height)
{
	renderTarget->Resize(width, height);
}

void ForwardRenderer::Initialize()
{
	renderTarget = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 1, true);
}

void ForwardRenderer::Clear()
{
	Clear(true, true, true);
}

void ForwardRenderer::RenderScene(Scene& p_scene,
	const Vector3& p_cameraPosition,
	const Camera& p_camera,
	const Frustum* p_customFrustum,
	Material* p_defaultMaterial)
{
	OpaqueDrawables	opaqueMeshes;
	TransparentDrawables transparentMeshes;


}

std::pair<ForwardRenderer::OpaqueDrawables, ForwardRenderer::TransparentDrawables> ForwardRenderer::FindAndSortDRawables(const Scene& p_scene, const Vector3 p_camPos, const Material& p_defaultMaterial)
{
	ForwardRenderer::OpaqueDrawables opaqueDrawables;
	ForwardRenderer::TransparentDrawables transparentDrawables;

	for (auto modelRender : p_scene.GetFastAccessComponents().modelRenderers)
	{
		if (modelRender->owner.IsActive())
		{
			//ÀëÏà»ú¾àÀë
			float distanceToActor = glm::distance(modelRender->owner.m_transform.GetWorldPosition(), p_camPos);

			if (auto materialRender = modelRender->owner.GetComponent<CMaterialRenderer>())
			{

			}




		}
	}


	return { opaqueDrawables, transparentDrawables };
}

void ForwardRenderer::DrawDrawable(const Drawable& p_toDraw)
{

}

void DrawMesh(Mesh& p_mesh, Material& p_material, Matrix4 p_mat4)
{

}

void ForwardRenderer::Clear(bool p_colorBuffer, bool p_deptBuffer, bool p_stencilColor)
{
	glClear(p_colorBuffer ? GL_COLOR_BUFFER_BIT : 0 |
		p_deptBuffer ? GL_DEPTH_BUFFER_BIT : 0 |
		p_stencilColor ? GL_STENCIL_BUFFER_BIT : 0
	);
}
