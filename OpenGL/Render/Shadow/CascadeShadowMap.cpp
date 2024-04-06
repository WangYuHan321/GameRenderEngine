#include "CascadeShadowMap.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../../Render/RenderTarget.h"
#include "../../Camera/Camera.h"
#include "../../Render/Mesh/Material.h"
#include "../../Core/ECS/Components/CDirectionalLight.h"

CascadeShadowMap::CascadeShadowMap()
{
	InitShadowMap(0, -5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 70.0f);
	InitShadowMap(1, -40.0f, 40.0f, -40.0f, 40.0f, 0.1f, 120.0f);
	InitShadowMap(2, -80.0f, 80.0f, -80.0f, 80.0f, 0.1f, 1360.0f);
	InitShadowMap(3, -160.0f, 160.0f, -160.0f, 160.0f, 0.1f, 2720.0f);
	InitShadowMap(4, -320.0f, 320.0f, -320.0f, 320.0f, 0.1f, 5440.0f);
}

void CascadeShadowMap::InitShadowMap(int level, float minX, float maxX, float miny, float maxY, float minz, float maxZ)
{
	m_pShadowMap[level].proj = glm::ortho<float>(minX, maxX, miny, maxY, minz, maxZ);
	RenderTarget* rt = new RenderTarget(1024, 1024, GL_UNSIGNED_BYTE, 0, true);
	rt->GetDepthStencilTexture()->Bind();
	rt->GetDepthStencilTexture()->SetFilterMin(GL_NEAREST);
	rt->GetDepthStencilTexture()->SetFilterMax(GL_NEAREST);
	rt->GetDepthStencilTexture()->SetWrapMode(GL_CLAMP_TO_BORDER);
	float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//???? glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER, border);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	m_pShadowMap[level].shadowMap = rt;
}

void CascadeShadowMap::BeginShadowRender(int level)
{
	currentLevel = level;
	glBindFramebuffer(GL_FRAMEBUFFER, m_pShadowMap[currentLevel].shadowMap->ID);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void CascadeShadowMap::EndFrame(Material* p_material)
{
	if (p_material)
	{
		for (unsigned int i = 0; i < 5; i++)
		{
			p_material->GetShader()->SetMatrix("shadow_lightDepthMat" + std::to_string(i), m_pShadowMap[i].depth);
			p_material->SetTextureValue("shadow_LightDepthMap" + std::to_string(i), m_pShadowMap[i].shadowMap->GetDepthStencilTexture());
		}
		p_material->SetBoolean("shadow_shadowCast", p_material->ShadowCast);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, previousFrameBuffer);
}

Matrix4 CascadeShadowMap::GetCurDepthMatrix4()
{
	return m_pShadowMap[currentLevel].depth;
}

void CascadeShadowMap::EndShadowRender()
{
	m_pShadowMap[currentLevel].depth = biasMatrix * m_pShadowMap[currentLevel].depth;
}

void CascadeShadowMap::BeginFrame(CDirectionalLight p_dirLight,const Camera* p_cam)
{
	const glm::vec3& cameraPosition = p_cam->Position;
	glm::vec3 target = glm::vec3(-cameraPosition.x, 0, -cameraPosition.z);
	glm::mat4 depthViewMatrix = glm::lookAt(target + (p_dirLight.GetDirectional() * 50.0f), target, glm::vec3(0, 1, 0));

	for (unsigned int i = 0; i < 5; i++)
	{
		m_pShadowMap[i].depth = m_pShadowMap[i].proj * depthViewMatrix;
	}

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFrameBuffer);
}

CascadeShadowMap::~CascadeShadowMap()
{
	for (auto item : m_pShadowMap)
	{
		if (item.shadowMap)
		{
			delete item.shadowMap;
			item.shadowMap = nullptr;
		}
	}
}