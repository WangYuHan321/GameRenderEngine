#include "ForwardRenderer.h"
#include "RenderTarget.h"
#include "../Camera/FlyCamera.h"

void ForwardRenderer::DoRender()
{

}

void ForwardRenderer::OnReSize(uint32 width, uint32 height)
{
	renderTarget->Resize(width, height);
}

void ForwardRenderer::Initialize()
{
	cam = new FlyCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	renderTarget = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 1, true);
}

void ForwardRenderer::Clear()
{
	Clear(true, true, true);
}

void ForwardRenderer::Clear(bool p_colorBuffer, bool p_deptBuffer, bool p_stencilColor)
{
	glClear(p_colorBuffer ? GL_COLOR_BUFFER_BIT : 0 |
		p_deptBuffer ? GL_DEPTH_BUFFER_BIT : 0 |
		p_stencilColor ? GL_STENCIL_BUFFER_BIT : 0
	);
}
