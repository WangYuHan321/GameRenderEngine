#include "CascadeShadowMap.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../../Render/RenderTarget.h"

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