#include "CascadeShadowMap.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../../Render/RenderTarget.h"
#include "../../Camera/Camera.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Render/Mesh/Material.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CDirectionalLight.h"

CascadeShadowMap::CascadeShadowMap()
{
	biasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	InitShadowMap(0, -5.0f, 5.0f, -5.0, 5.0f, 0.1f, 40.0f);
	InitShadowMap(1, -400.0f, 400.0f, -400.0f, 400.0f, 0.1f, 120.0f);
	//InitShadowMap(2, -80.0f, 80.0f, -80.0f, 80.0f, 0.1f, 1360.0f);
	//InitShadowMap(3, -160.0f, 160.0f, -160.0f, 160.0f, 0.1f, 2720.0f);
	//InitShadowMap(4, -320.0f, 320.0f, -320.0f, 320.0f, 0.1f, 5440.0f);
}

void CascadeShadowMap::InitShadowMap(int level, float minX, float maxX, float miny, float maxY, float minz, float maxZ)
{
	m_pShadowMap[level].proj = glm::ortho<float>(minX, maxX, miny, maxY, minz, maxZ);
	RenderTarget* rt = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 0, true);
	rt->GetDepthStencilTexture()->Bind();
	rt->GetDepthStencilTexture()->SetFilterMin(GL_NEAREST);
	rt->GetDepthStencilTexture()->SetFilterMax(GL_NEAREST);
	rt->GetDepthStencilTexture()->SetWrapMode(GL_CLAMP_TO_BORDER);
	float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//???? glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER, border);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	m_pShadowMap[level].shadowMap = rt;
}

void CascadeShadowMap::Clear()
{
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFrameBuffer);
	for (int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_pShadowMap[i].shadowMap->ID);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, previousFrameBuffer);
}

void CascadeShadowMap::BeginShadowRender(int level)
{
	currentLevel = level;
	glBindFramebuffer(GL_FRAMEBUFFER, m_pShadowMap[currentLevel].shadowMap->ID);
	//glClear(GL_DEPTH_BUFFER_BIT);
}

void CascadeShadowMap::SetShadowMap(Material* p_material)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		p_material->SetTextureValue("shadow_LightDepthMap" + std::to_string(i), m_pShadowMap[i].shadowMap->GetDepthStencilTexture());
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		p_material->GetShader()->SetMatrix("shadow_lightDepthMat" + std::to_string(i), m_pShadowMap[i].depth);
		//LOG_ERROR(glm::to_string(m_pShadowMap[i].depth));
	}
	p_material->SetBoolean("shadow_shadowReceive", p_material->ShadowReceive);
}

Matrix4 CascadeShadowMap::GetCurDepthMatrix4()
{
	//LOG_INFO(glm::to_string(m_pShadowMap[currentLevel].depth));
	return m_pShadowMap[currentLevel].depth;
}

void CascadeShadowMap::InitializeFrame(CDirectionalLight p_dirLight, const Camera* p_cam)
{
	const glm::vec3& cameraPosition = p_cam->Position;
	glm::vec3 target = glm::vec3(cameraPosition.x, p_dirLight.owner.m_transform.GetWorldPosition().y, cameraPosition.z);
	glm::mat4 depthViewMatrix = glm::lookAt(target - p_dirLight.GetDirectional(), target, p_cam->Up);

	int test[2] = { 5.0f, 400.0f };

	for (unsigned int i = 0; i < 2; i++)
	{
		const auto _near = p_cam->Near;
		const auto _far = p_cam->Far;
		const auto _size = test[i];

		const auto right = 1.0 * _size;
		const auto left = -right;
		const auto top = _size;
		const auto bottom = -top;

		FTransform cam(target + p_dirLight.GetDirectional(), target, p_cam->Up);

		const auto a = (Quaternion)cam.GetWorldRotation() * Vector3{ left, top, 0 };
		const auto b = (Quaternion)cam.GetWorldRotation() * Vector3{ right, top, 0 };
		const auto c = (Quaternion)cam.GetWorldRotation() * Vector3{ left, bottom, 0 };
		const auto d = (Quaternion)cam.GetWorldRotation() * Vector3{ right, bottom, 0 };
		m_pDebugOrtho[i] = { cam.GetWorldPosition(), (Quaternion)cam.GetWorldRotation() * Vector3(0.0f, 0.0f, 1.0f), _near, _far, a, b, c, d, a, b, c, d };
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		m_pShadowMap[i].depth = m_pShadowMap[i].proj * depthViewMatrix;
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		m_pShadowMap[i].depth = biasMatrix * m_pShadowMap[i].depth;
	}
}

void CascadeShadowMap::EndShadowRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, previousFrameBuffer);
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

int CascadeShadowMap::GetShadowMap(int curLevel)
{
	if(curLevel < 2)
		return m_pShadowMap[curLevel].shadowMap->GetDepthStencilTexture()->ID;
	return 0;
}

DebugOrthographics CascadeShadowMap::GetOrthographicFrustum(int curLevel)
{
	return m_pDebugOrtho[curLevel];
}