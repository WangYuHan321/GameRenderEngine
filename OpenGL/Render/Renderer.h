#pragma once
#include"GLCache.h"
#include"../Render/Mesh/Mesh.h"
#include"../Render/Mesh/Material.h"
#include"../Scene/SceneNode.h"
#include "../Event/Event.h"

class PBR;
class Quad;
class Camera;
class PointLight;
class PostProcess;
class RenderTarget;
class CommandBuffer;
class RenderCommand;
class MaterialLibrary;
class DirectionalLight;


class Renderer 
{
public:
	GLCache m_glCache;
	glm::mat4 m_prevViewProjection;
	Quad* m_quadNDC;
	Camera* m_camera;
	RenderTarget* m_gBuffer;
	PostProcess* m_postProcess;
	RenderTarget* m_customTarget;
	CommandBuffer* m_commandBuffer;
	MaterialLibrary* m_MaterialLibrary;
	RenderTarget* m_currentRenderTarget;
	listenerID m_frameReSizeListener;
	PBR* m_pbrCapture;

	uint32 m_globalUBO; 
	glm::vec2 m_renderSize;
	bool enableWireframe = false;
	bool enableShadows = true;

	uint32 m_frameBufferCubeMapID;
	uint32 m_framebufferCubeMapRBO;

	//方向光
	std::vector<DirectionalLight*>m_directionalLights;
	std::vector<RenderTarget*> m_shadowRenderTarget;
	//点光源 灯泡
	std::vector<PointLight*> m_pointLights;
	//自定义前向渲染
	std::vector<RenderTarget*> m_renderTargetsCustom;

public:

	Renderer();
	~Renderer();

	void Init();
	void UpdateUBO();
	void PushRender(Mesh* mesh,Material* material,glm::mat4 transofrm = glm::mat4(1.0), glm::mat4 prevTransoform = glm::mat4(1.0));
	void PushRender(SceneNode* node);
	void PushPostProcessor(Material* postProcessor);
	void AddDirLight(DirectionalLight* directionLight);
	void AddPointLight(PointLight* pointLight);
	void SetRenderSize(uint32 width, uint32 height);

	Camera* GetCamera() { return m_camera; }
	RenderTarget* GetCurrentRenderTarget();
	Material* CreateMaterial(std::string name = "default");

	void RenderDeferredAmbient();
	void RenderPushedCommands();
	void RenderMesh(Mesh* mesh);
	void RenderToCubeMap(SceneNode* sceneNode, TextureCube* textureCube, uint32 mip = 0);
	void RenderToCubeMap(std::vector<RenderCommand>& renderCommands, TextureCube* textureCube, uint32 mip);
	void RenderCustomCommand(RenderCommand* command, Camera* customCamera, bool updateGLState = true);
	void RenderShadowCastCommand(RenderCommand* command, const glm::mat4& porj, const glm::mat4& view);
	
	void Blit(Renderer* render, Texture* src);
	void Blit(RenderTarget* renderTarget, Material* renderMaterial);
	//void Blit(Texture* src, RenderTarget* dst = nullptr, Material* material = nullptr, std::string texturUniform = "TexSrc");

	void SetCamera(Camera* cam) { m_camera = cam; }
};