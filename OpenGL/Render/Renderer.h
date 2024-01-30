#pragma once
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform.hpp>
#include"GLCache.h"
#include"../Render/Mesh/Mesh.h"
#include"../Render/Mesh/Material.h"
#include"../Scene/SceneNode.h"
#include "../Event/Event.h"

class PBR;
class Quad;
class Sphere;
class Camera;
class Window;
class PBRCapture;
class PointLight;
class PostProcess;
class RenderTarget;
class GlobalContext;
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
	RenderTarget* m_gBuffer;
	PostProcess* m_postProcess;
	RenderTarget* m_customTarget;
	CommandBuffer* m_commandBuffer;
	MaterialLibrary* m_materialLibrary;
	RenderTarget* m_currentRenderTargetCustom;
	listenerID m_frameReSizeListener;
	PBR* m_pbrCapture;

	uint32 m_globalUBO; 
	glm::vec2 m_renderSize;

	uint32 m_frameBufferCubeMapID;
	uint32 m_frameBufferCubeMapRBO;

	//点光源模型
	Sphere* m_deferredPointMesh;

	//Probe Position
	std::vector<glm::vec4> m_probeSaptials;

	//方向光
	std::vector<DirectionalLight*>m_directionalLights;
	std::vector<RenderTarget*> m_shadowRenderTarget;
	//点光源 灯泡
	std::vector<PointLight*> m_pointLights;
	//自定义前向渲染
	std::vector<RenderTarget*> m_renderTargetsCustom;

	uint32 blitToFrameID = 0;

	bool enableIrradianceGI = false;
	bool enableLights = true;
	bool enableWireframe = false;
	bool enableShadows = true;
	bool enableDebugLight = true;
	bool enableDebugGBuffer = false;


	std::vector<RenderCommand> test;
public:

	Renderer(GlobalContext& p_context);
	~Renderer();

	void Init();
	void Clear();
	void InitSkyBox(Camera& cam);
	void UpdateUBO(Camera& cam);
	void SetTarget(RenderTarget* renderTarget, GLenum type);
	void PushRender(Mesh* mesh,Material* material,glm::mat4 transofrm = glm::mat4(1.0), glm::mat4 prevTransoform = glm::mat4(1.0));
	void PushRender(SceneNode* node);
	void SetRenderSize(uint32 width, uint32 height);
	void PushPostProcessor(Material* postProcessor);
	void AddDirLight(DirectionalLight* directionLight);
	void AddPointLight(PointLight* pointLight);
	void AddIrradianceProbe(glm::vec3 pos, float radiuse);


	RenderTarget* GetCurrentRenderTarget();
	Material* CreateMaterial(std::string name = "default");

	void RenderPushedCommands(Camera& cam);
	void RenderMesh(Mesh* mesh);
	void RenderToCubeMap(SceneNode* sceneNode, Camera& cam, TextureCube* textureCube, uint32 mip = 0);
	void RenderToCubeMap(std::vector<RenderCommand>& renderCommands, TextureCube* textureCube,
		glm::vec3 position, uint32 mip);
	void RenderCustomCommand(RenderCommand* command, Camera* customCamera, bool updateGLState = true);
	void RenderShadowCastCommand(RenderCommand* command, const glm::mat4& porj, const glm::mat4& view);
	
	void RenderDeferredAmbient(Camera& cam);
	void RenderDeferredDirLight(DirectionalLight* light, Camera& cam);
	void RenderDeferredPointLight(PointLight* light, Camera& cam);

	void Blit(RenderTarget* renderTarget, Material* renderMaterial);
	//void Blit(Texture* src, RenderTarget* dst = nullptr, Material* material = nullptr, std::string texturUniform = "TexSrc");

	void BakeProbes(SceneNode* scene = nullptr, Camera* cam = nullptr);
	PBRCapture* GetSkyCapture();

private:
	GlobalContext& m_context;
};