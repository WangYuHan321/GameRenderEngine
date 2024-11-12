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

void ShadowMap::Clear()
{
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFrameBuffer);
	glGetIntegerv(GL_VIEWPORT, previousViewport);
	glBindFramebuffer(GL_FRAMEBUFFER, m_renderTarget->ID);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, previousFrameBuffer);
}

void ShadowMap::InitializeFrame(CDirectionalLight dirLight, const Camera* p_cam)
{
	const auto _size = 20.0f;

	const auto _near = 0.1f;
	const auto _far = 20.0f;
	glm::mat4 lightProject = glm::ortho(-250.0f, 250.0f, -250.0f, 250.0f, 0.1f, 500.0f);
	glm::vec3 target = glm::vec3(-dirLight.GetPosition().x, 0, -dirLight.GetPosition().z);
	glm::mat4 lightView = glm::lookAt(target - (dirLight.GetDirectional() * 100.0f), target,  glm::vec3(0,1,0) );
	m_lightMatrix = lightProject * lightView;
}

void ShadowMap::SetShadowMap(Material* p_material)
{
	p_material->SetTextureValue("shadow_LightDepthMap0", m_renderTarget->GetDepthStencilTexture());
	p_material->SetMatrix("shadow_lightDepthMat0", m_lightMatrix);
	p_material->SetBoolean("shadow_shadowReceive", p_material->ShadowReceive);
}

void ShadowMap::BeginShadow()
{
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_renderTarget->ID);

	glViewport(0, 0, m_renderTarget->Width, m_renderTarget->Height);
}

void ShadowMap::EndShadow()
{
	glBindFramebuffer(GL_FRAMEBUFFER, previousFrameBuffer);
	glViewport(previousViewport[0], previousViewport[1], previousViewport[2], previousViewport[3]);
}

Matrix4 ShadowMap::GetCurDepthMatrix4()
{
	return m_lightMatrix;
}

int ShadowMap::GetShadowMap(int id)
{
	return m_renderTarget->GetDepthStencilTexture()->ID;
}

DebugOrthographics ShadowMap::GetOrthographicFrustum(int curLevel)
{
	return m_debugOrtho;
}