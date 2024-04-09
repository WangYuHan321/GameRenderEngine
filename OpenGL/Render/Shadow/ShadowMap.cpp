#include "ShadowMap.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../../Render/RenderTarget.h"
#include "../../Camera/Camera.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Render/Mesh/Material.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CDirectionalLight.h"

ShadowMap::ShadowMap()
{
	m_renderTarget = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 0, true);
	m_renderTarget->GetDepthStencilTexture()->Bind();
	m_renderTarget->GetDepthStencilTexture()->SetFilterMin(GL_NEAREST);
	m_renderTarget->GetDepthStencilTexture()->SetFilterMax(GL_NEAREST);
	m_renderTarget->GetDepthStencilTexture()->SetWrapMode(GL_CLAMP_TO_BORDER);
	float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//???? glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER, border);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
}

ShadowMap::~ShadowMap()
{
	if (m_renderTarget)
		delete m_renderTarget;
}

void ShadowMap::BeginShadow()
{
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_renderTarget->ID);
}

void ShadowMap::EndShadow()
{
	glBindFramebuffer(GL_FRAMEBUFFER, previousFrameBuffer);
}