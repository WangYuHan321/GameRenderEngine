#pragma once
#include<GLM/glm.hpp>
class RenderTarget;
class DirectionalLight
{
public:
	glm::vec3 Direction = glm::vec3(0.0f);
	glm::vec3 Color = glm::vec3(1.0f);
	float Intensity = 1.0f;

	bool CastShadow = true;
	RenderTarget* ShadowMapRT = NULL;
	glm::mat4 LightSpaceViewProjection;

};

