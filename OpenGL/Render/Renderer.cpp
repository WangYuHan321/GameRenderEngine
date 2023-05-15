#include <stack>
#include <GLM/gtx/transform.hpp>

#include "PBR.h"
#include "Mesh/Quad.h"
#include "Renderer.h"
#include "PostProcess.h"
#include "RenderTarget.h"
#include "Lighting/DirectionalLight.h"
#include "Material/MaterialLibrary.h"
#include "../Camera/Camera.h"
#include "../pbr_capture.h"
#include "Mesh/Sphere.h"
#include "../Render/CommandBuffer.h"
#include "../Render/RenderCommand.h"
#include "../Util/Utils.h"
#include "../Window/GLFWWindow.h"
#include "Lighting/PointLight.h"
#include "../Window/Window.h"
#include "Resource/ResourceManager.h"


Renderer::Renderer()
{
	Init();
	m_frameReSizeListener = Window::getInstance()->ReSizeWindowEvent.
	AddListenerID(std::bind(&Renderer::SetRenderSize, this, std::placeholders::_1, std::placeholders::_2));
}

Renderer::~Renderer()
{
	delete m_quadNDC;
	delete m_gBuffer;
	delete m_pbrCapture;
	delete m_postProcess;
	delete m_customTarget;
	delete m_commandBuffer;
	delete m_materialLibrary;
	//delete m_currentRenderTarget;

	//for (auto item : m_directionalLights)
	//	delete item;
	for (auto item : m_shadowRenderTarget)
		delete item;
	//for (auto item : m_pointLights)
	//	delete item;
	for (auto item : m_renderTargetsCustom)
		delete item;
	Window::getInstance()->ReSizeWindowEvent.RemoveListenerID(m_frameReSizeListener);
}

void Renderer::PushRender(Mesh* mesh, Material* material, glm::mat4 transofrm, glm::mat4 prevTransoform)
{
	//当是mesh material 传进来 默认是rendertarget为空
	//Material materType 指定传进来是默认还是指定特定的用法
	RenderTarget* curRenderTarget = GetCurrentRenderTarget();
	m_commandBuffer->Push(mesh, material, transofrm, prevTransoform, glm::vec3(-99999.0f), glm::vec3(99999.0f), curRenderTarget);
}
void Renderer::PushRender(SceneNode* node)
{
	node->UpdateTransform(true);

	RenderTarget* target = GetCurrentRenderTarget();

	std::stack<SceneNode*> nodeStack;
	nodeStack.push(node);
	for (unsigned int i = 0; i < node->GetChildCount(); i++)
		nodeStack.push(node->GetChildByIndex(i));


	while (!nodeStack.empty())
	{
		SceneNode * node = nodeStack.top();//如果是root 是空 根节点记录父节点指针
		nodeStack.pop();
		if (node->Mesh)
		{
			glm::vec3 boxMinWorld = node->GetWorldPos() + (node->GetWorldScale() * node->m_BoxMin);
			glm::vec3 boxMaxWorld = node->GetWorldPos() + (node->GetWorldScale() * node->m_BoxMax);
			m_commandBuffer->Push(node->Mesh, node->Material, node->GetTransform(), node->GetPrevTransform(), boxMinWorld, boxMaxWorld, target);
		}

		for (unsigned int i = 0; i < node->GetChildCount(); i++)
			nodeStack.push(node->GetChildByIndex(i));
	}
}
void Renderer::PushPostProcessor(Material* postProcessor)
{
	//Material Type == PostProcessor
	m_commandBuffer->Push(nullptr, postProcessor);
}

void Renderer::UpdateUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_globalUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &(m_camera->Projection * m_camera->View)[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, 64, sizeof(glm::mat4), &m_prevViewProjection[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, 128, sizeof(glm::mat4), &m_camera->Projection[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, 192, sizeof(glm::mat4), &m_camera->View[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, 256, sizeof(glm::mat4), &m_camera->View[0][0]);

	glBufferSubData(GL_UNIFORM_BUFFER, 320, sizeof(glm::vec4), &m_camera->Position[0]);

#if 0
	printf("--------------------projection------------------------------\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("[%f]", m_camera->Projection[i][j]);
		}
		printf("\n");
	}
	printf("--------------------View-------------------------------------\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("[%f]", m_camera->View[i][j]);
		}
		printf("\n");
	}
	printf("--------------------Position-------------------------------------\n");
	for (int i = 0; i < 3; i++)
	{
		printf("[%f]", m_camera->Position[i]);
		if (i == 2)
			printf("\n");
	}
	printf("FOV = %f \n", m_camera->FOV);
#endif


	unsigned int stride = 2 * sizeof(glm::vec4);
	for (unsigned int i = 0; i < m_directionalLights.size() && i < 4; ++i) // no more than 4 directional lights
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 336 + i * stride, sizeof(glm::vec4), &m_directionalLights[i]->Direction[0]);
		glBufferSubData(GL_UNIFORM_BUFFER, 336 + i * stride + sizeof(glm::vec4), sizeof(glm::vec4), &m_directionalLights[i]->Color[0]);
	}
	for (unsigned int i = 0; i < m_pointLights.size() && i < 8; ++i) //  constrained to max 8 point lights in forward context
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 464 + i * stride, sizeof(glm::vec4), &m_pointLights[i]->Position[0]);
		glBufferSubData(GL_UNIFORM_BUFFER, 464 + i * stride + sizeof(glm::vec4), sizeof(glm::vec4), &m_pointLights[i]->Color[0]);
	}

}

void Renderer::Init()
{
	m_renderSize = glm::vec2(1920, 1080);
	m_commandBuffer = new CommandBuffer(this);

	m_glCache.SetDepthTest(true);
	m_glCache.SetCull(true);

	m_glCache.SetDepthTest(true);
	m_glCache.SetCull(true);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); // 天空盒空袭细缝采样填充

	glViewport(0.0f, 0.0f, m_renderSize.x, m_renderSize.y);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	glGenFramebuffers(1, &m_frameBufferCubeMapID);
	glGenRenderbuffers(1, &m_frameBufferCubeMapRBO);

	for (int i = 0; i < 4; i++)
	{
		RenderTarget* rt = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 1, true);
		rt->m_depthStencil.Bind();
		rt->m_depthStencil.SetFilterMin(GL_NEAREST);
		rt->m_depthStencil.SetFilterMax(GL_NEAREST);
		rt->m_depthStencil.SetWrapMode(GL_CLAMP_TO_BORDER);
		float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//???? glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER, border);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
		m_shadowRenderTarget.push_back(rt);
	}
	m_quadNDC = new Quad;
	m_camera = new Camera();
	m_pbrCapture = new PBR(this);
	m_postProcess = new PostProcess(this);
	m_deferredPointMesh = new Sphere(16, 16);
	m_materialLibrary = new MaterialLibrary();
	m_customTarget = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, true);
	m_gBuffer = new RenderTarget(m_renderSize.x, m_renderSize.y, GL_HALF_FLOAT, 4, true);

	glGenBuffers(1, &m_globalUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, m_globalUBO);
	glBufferData(GL_UNIFORM_BUFFER, 720, nullptr, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_globalUBO);

	Texture* hdrMap = ResourceManager::getInstance()->LoadHDRTexture("sky env",
		"Asset\\texture\\backgrounds\\alley.hdr");
	PBRCapture* envBridge = m_pbrCapture->ProcessEquirectangular(hdrMap);
	m_pbrCapture->SetSkyCapture(envBridge);
}

void Renderer::AddDirLight(DirectionalLight* directionLight)
{
	m_directionalLights.push_back(directionLight);
}

void Renderer::AddPointLight(PointLight* pointLight)
{
	m_pointLights.push_back(pointLight);
}


void Renderer::SetRenderSize(uint32 width, uint32 height)
{
	m_renderSize.x = width;
	m_renderSize.y = height;

	m_gBuffer->Resize(width, height);

	m_customTarget->Resize(width, height);

	m_postProcess->Resize(width, height);

	Log("Set Render Size (%d, %d) \n", width, height );
}

Material* Renderer::CreateMaterial(string name)
{
	if (m_materialLibrary->CreateMaterial(name) == nullptr)
	{
		Log("no material!!!!\n");
	}
	return m_materialLibrary->CreateMaterial(name);
}

//参数 渲染命令 自定义相机 是否改变全局状态
void Renderer::RenderCustomCommand(RenderCommand* command, Camera* customCamera, bool updateGLState)
{
	Material* material = command->material;
	Mesh* mesh = command->mesh;

	//需要变更全局state
	if (updateGLState)
	{
		m_glCache.SetBlend(material->Blend);
		if (material->Blend)
		{
			m_glCache.SetBlendFunc(material->BlendSrc, material->BlendDst);
		}

		m_glCache.SetDepthFunction(material->DepthCompare);
		m_glCache.SetDepthTest(material->DepthTest);
		m_glCache.SetCull(material->Cull);
		m_glCache.SetCullFace(material->CullFace);
	}

	material->GetShader()->activeShader();
	
	if (customCamera)
	{
		material->GetShader()->SetMatrix("projection", customCamera->Projection);
		material->GetShader()->SetMatrix("view", customCamera->View);
		material->GetShader()->SetVector("CamPos", customCamera->Position);
	}

	material->GetShader()->SetMatrix("model", command->Transfrom);
	material->GetShader()->SetMatrix("prevModel", command->prevTransform);
	material->GetShader()->SetBool("ShadowsEnabled", enableShadows);

	if (enableShadows && material->Type == MATERIAL_CUSTOM && material->ShadowReceive)
	{
		for (uint32 i = 0; i < m_directionalLights.size(); i++)
		{
			if (m_directionalLights[i]->ShadowMapRT)
			{
				material->GetShader()->SetMatrix("lightShadowViewProjection" + std::to_string(i + 1), m_directionalLights[i]->LightSpaceViewProjection);
				m_directionalLights[i]->ShadowMapRT->GetDepthStencilTexture()->Bind(10 + i);
			}
		}
	}

	//设置Shader中的数据
	auto* samplers = material->GetSamplerUniforms();
	for (auto it = samplers->begin(); it != samplers->end(); it++)
	{
		if (it->second.Type == SHADER_SAMPLERCUBE)
			it->second.TEXTURE_CUBE->Bind(it->second.ID);
		else
			it->second.TEXTURE->Bind(it->second.ID);
	}

	auto* uniforms = material->GetUniforms();
	for (auto it = uniforms->begin(); it != uniforms->end(); it++)
	{

		switch (it->second.Type)
		{
		case SHADER_BOOL:
			material->GetShader()->SetBool(it->first, it->second.BOOL);
			break;
		case SHADER_INT:
			material->GetShader()->SetInt(it->first, it->second.INT);
			break;
		case SHADER_FLOAT:
			material->GetShader()->SetFloat(it->first, it->second.FLOAT);
			break;
		case SHADER_VEC2:
			material->GetShader()->SetVector(it->first, it->second.VEC2);
			break;
		case SHADER_VEC3:
			material->GetShader()->SetVector(it->first, it->second.VEC3);
			break;
		case SHADER_VEC4:
			material->GetShader()->SetVector(it->first, it->second.VEC4);
			break;
		case SHADER_MAT2:
			material->GetShader()->SetMatrix(it->first, it->second.MAT2);
			break;
		case SHADER_MAT3:
			material->GetShader()->SetMatrix(it->first, it->second.MAT3);
			break;
		case SHADER_MAT4:
			material->GetShader()->SetMatrix(it->first, it->second.MAT4);
			break;
		default:
			gLog.OutputError("error shader uniform type!!!");
			break;
		}

	}
	RenderMesh(command->mesh);
}

void Renderer::RenderMesh(Mesh * mesh)
{
	glBindVertexArray(mesh->m_VAO);
	if (mesh->Indices.size() > 0)
	{
		glDrawElements(mesh->Topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, mesh->Indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(mesh->Topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, 0, mesh->Positions.size());
	}

}

void Renderer::RenderToCubeMap(SceneNode* sceneNode, TextureCube* textureCube, uint32 mip)
{
	CommandBuffer commandBuffer(this);
	commandBuffer.Push(sceneNode->Mesh, sceneNode->Material, sceneNode->GetTransform());

	//printf("%f %f %f %f \n", sceneNode->GetTransform()[0][0],
	//	sceneNode->GetTransform()[1][0], sceneNode->GetTransform()[2][0], sceneNode->GetTransform()[3][0]);
	//printf("%f %f %f %f \n", sceneNode->GetTransform()[0][1],
	//	sceneNode->GetTransform()[1][1], sceneNode->GetTransform()[2][1], sceneNode->GetTransform()[3][1]);
	//printf("%f %f %f %f \n", sceneNode->GetTransform()[0][2],
	//	sceneNode->GetTransform()[1][2], sceneNode->GetTransform()[2][2], sceneNode->GetTransform()[3][2]);
	//printf("%f %f %f %f \n", sceneNode->GetTransform()[0][3],
	//	sceneNode->GetTransform()[1][3], sceneNode->GetTransform()[2][3], sceneNode->GetTransform()[3][3]);

	std::stack<SceneNode*> childStack;
	for (uint32 i = 0; i < sceneNode->GetChildCount(); ++i)
		childStack.push(sceneNode->GetChildByIndex(i));
	while (!childStack.empty())
	{
		SceneNode* child = childStack.top();
		childStack.pop();
		commandBuffer.Push(child->Mesh, child->Material, child->GetTransform());
		for (uint32 i = 0; i < child->GetChildCount(); ++i)
			childStack.push(child->GetChildByIndex(i));
	}
	commandBuffer.Sort();
	std::vector<RenderCommand> renderCommands = commandBuffer.GetCustomRenderCommand(nullptr);

	RenderToCubeMap(renderCommands, textureCube, mip);
}

void Renderer::RenderToCubeMap(std::vector<RenderCommand>& renderCommands, TextureCube* textureCube, uint32 mip)
{
	Camera faceCameras[6] = {
		Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f,-1.0f)),
		Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};
	float width = (float)textureCube->FaceWidth * pow(0.5, mip);
	float height = (float)textureCube->FaceHeight * pow(0.5, mip);

	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferCubeMapID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_frameBufferCubeMapRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_frameBufferCubeMapRBO);

	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferCubeMapID);

	for (uint32 i = 0; i < 6; ++i)
	{
		Camera* camera = &faceCameras[i];
		camera->SetPerspective(Deg2Rad(90.0f), width / height, 0.1f, 100.0f);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, textureCube->ID, mip);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (uint32 i = 0; i < renderCommands.size(); ++i)
		{
			assert(renderCommands[i].Material->Type == MATERIAL_CUSTOM);
			RenderCustomCommand(&renderCommands[i], camera); 
		}

	}
}

void Renderer::RenderPushedCommands()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_commandBuffer->Sort();
	UpdateUBO();

	m_glCache.SetBlend(false);
	m_glCache.SetCull(true);
	m_glCache.SetCullFace(GL_BACK);
	m_glCache.SetDepthTest(true);
	m_glCache.SetDepthFunction(GL_LESS);
	
	// first step :  geometry buffer
	std::vector<RenderCommand> deferredRenderCommand = m_commandBuffer->GetDeferredRenderCommand(true);
	glViewport(0, 0, m_renderSize.x, m_renderSize.y);
	glBindFramebuffer(GL_FRAMEBUFFER, m_gBuffer->ID);
	unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 ,GL_COLOR_ATTACHMENT2 ,GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_glCache.SetPolyonMode(enableWireframe ? GL_LINE : GL_FILL);//实体填充
	for (unsigned int i = 0; i < deferredRenderCommand.size(); i++)
	{
		RenderCustomCommand(&deferredRenderCommand[i], nullptr, false);
	}

	//attachments[0] = GL_NONE; // disable for next pass (shadow map generation)
	m_glCache.SetPolyonMode(GL_FILL);
	attachments[1] = GL_NONE;
	attachments[2] = GL_NONE;
	attachments[3] = GL_NONE;
	glDrawBuffers(4, attachments);

	//处理阴影
	if (enableShadows)
	{
		m_glCache.SetCullFace(GL_FRONT);
		std::vector<RenderCommand> shadowCommands = m_commandBuffer->GetShadowCastRenderCommands();

		unsigned int shadowRtIndex = 0;

		//m_ShadowRenderTarget只运行4个灯光渲染
		
		//方向光阴影的渲染
		for (int i = 0; i < m_directionalLights.size(); i++)
		{
			DirectionalLight* light = m_directionalLights[i];
			if (light->CastShadow)
			{
				m_materialLibrary->dirShadowShader->activeShader();
				glBindFramebuffer(GL_FRAMEBUFFER, m_shadowRenderTarget[shadowRtIndex]->ID);
				glViewport(0, 0, m_shadowRenderTarget[shadowRtIndex]->Width, m_shadowRenderTarget[shadowRtIndex]->Height);
				glClear(GL_DEPTH_BUFFER_BIT);

				glm::mat4 lightProject = glm::ortho(-20.0f, 20.0f, 20.0f, -20.0f, -15.0f, 20.0f);
				glm::mat4 lightView = glm::lookAt(-light->Direction * 10.0f, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
				m_directionalLights[i]->LightSpaceViewProjection = lightProject * lightView;
				m_directionalLights[i]->ShadowMapRT = m_shadowRenderTarget[shadowRtIndex];
				for (int j = 0; j < shadowCommands.size(); j++)
				{
					RenderShadowCastCommand(&shadowCommands[j], lightProject, lightView);
				}
				++shadowRtIndex;
			}
		}
		m_glCache.SetCullFace(GL_BACK);
	}

	//----------------------------
	//重新设置状态
	attachments[0] = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(4, attachments);

	//SSAO 保存在PostPrwocess下的m_ssaoRenderTarget
	m_postProcess->ProcessPreLighting();
	//-------------------------

	//--------------------------
	glBindFramebuffer(GL_FRAMEBUFFER, m_customTarget->ID);
	glViewport(0, 0, m_customTarget->Width, m_customTarget->Height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//延迟光照
	//关闭深度测试 开启混合
	m_glCache.SetDepthTest(false);
	m_glCache.SetBlend(true);
	m_glCache.SetBlendFunc(GL_ONE, GL_ONE);

	//GBuffer
	m_gBuffer->GetColorTexture(0)->Bind(0);
	m_gBuffer->GetColorTexture(1)->Bind(1);
	m_gBuffer->GetColorTexture(2)->Bind(2);

	//渲染环境光照
	//使用SSAO 和Cook-Torance模型 记录 m_customTarget
	RenderDeferredAmbient();

	if (enableLights)
	{

		//方向光照
		for (auto it = m_directionalLights.begin(); it != m_directionalLights.end(); ++it)
		{
			RenderDeferredDirLight(*it);
		}

		//点光源
		m_glCache.SetCull(GL_FRONT);
		for (auto it = m_pointLights.begin(); it != m_pointLights.end(); ++it)
		{
			//粗粒度处理
			if (m_camera->Frustum.Intersect((*it)->Position, (*it)->Radius))
			{
				RenderDeferredPointLight(*it);
			}
		}
		m_glCache.SetCull(GL_BACK);
	}

	//-----------------------

	m_glCache.SetDepthTest(true);
	m_glCache.SetBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	m_glCache.SetBlend(false);
	
	//自定义渲染

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_gBuffer->ID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_customTarget->ID);
	glBlitFramebuffer(0, 0, m_gBuffer->Width, m_gBuffer->Height,
		0, 0, m_renderSize.x, m_renderSize.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

	m_renderTargetsCustom.push_back(nullptr);//这个是默认渲染物体
	for (uint32 targetIndex = 0; targetIndex < m_renderTargetsCustom.size(); targetIndex++)
	{
		RenderTarget* renderTarget = m_renderTargetsCustom[targetIndex];
		if (renderTarget)
		{

		}
		else
		{
			//渲染默认的framebuffer
			glViewport(0, 0, m_renderSize.x, m_renderSize.y);
			glBindFramebuffer(GL_FRAMEBUFFER, m_customTarget->ID);
			m_camera->SetPerspective(m_camera->FOV, m_renderSize.x / m_renderSize.y, 0.1f, 100.0f);
		}

		std::vector<RenderCommand> renderCommands = m_commandBuffer->GetCustomRenderCommand(renderTarget);

		m_glCache.SetPolyonMode(enableWireframe ? GL_LINE : GL_FILL);
		for (uint32 i = 0; i < renderCommands.size(); i++)
		{
			RenderCustomCommand(&renderCommands[i], nullptr);
		}
		m_glCache.SetPolyonMode(GL_FILL);
	}

	//透明材质渲染
	glViewport(0, 0, m_renderSize.x, m_renderSize.y);
	glBindFramebuffer(GL_FRAMEBUFFER, m_customTarget->ID);
	std::vector<RenderCommand> alphaRenderCommand = m_commandBuffer->GetAlphaRenderCommand();
	for (uint32 i = 0; i < alphaRenderCommand.size(); ++i)
	{
		RenderCustomCommand(&alphaRenderCommand[i], nullptr);
	}

	//bloom
	m_postProcess->ProcessPostLighting(m_customTarget);

	//Debug PointLight Mesh

	m_glCache.SetPolyonMode(GL_LINE);
	m_glCache.SetCullFace(GL_FRONT);
	for (auto it = m_pointLights.begin(); it != m_pointLights.end(); it++)
	{
		if ((*it)->RenderMesh)
		{
			m_materialLibrary->debugLightMaterial->SetVector("lightColor", 
				(*it)->Color * (*it)->Intensity * 0.25f);

			RenderCommand command;
			command.material = m_materialLibrary->debugLightMaterial;
			command.mesh = m_deferredPointMesh;
			glm::mat4 model;
			glm::translate(model, (*it)->Position);
			glm::scale(model, glm::vec3(0.25f));
			command.Transfrom = model;

			RenderCustomCommand(&command, nullptr);
		}
	}
	m_glCache.SetPolyonMode(GL_FILL);
	m_glCache.SetCullFace(GL_BACK);

	std::vector<RenderCommand>postProcessingCommands = m_commandBuffer->GetPostProcessRenderCommand();

	for (unsigned int i = 0; i < postProcessingCommands.size(); ++i)
	{

	}

	m_postProcess->Blit(m_customTarget);

	m_prevViewProjection = m_camera->Projection * m_camera->View;

	m_commandBuffer->Clear();

	m_renderTargetsCustom.clear();

}

void Renderer::RenderDeferredAmbient()
{
	//Material 内置函数
	PBRCapture* skyCapture = m_pbrCapture->GetSkyCapture();
	auto irradianceProbe = m_pbrCapture->m_pbrCaputreProbe;

	if (enableIrradianceGI && irradianceProbe.size() > 0)
	{
		// 3 irradiance 4 prwefilterwmap 5 brdf lut 6 ssao
		skyCapture->PrefilteredMap->Bind(4);
		m_pbrCapture->m_renderTargetBRDFLut->GetColorTexture(0)->Bind(5);
		m_postProcess->SSAOOutput->Bind(6);

		m_glCache.SetCullFace(GL_FRONT);
		for (uint32 i = 0; i < irradianceProbe.size(); i++)
		{
			PBRCapture* probe = irradianceProbe[i];

			if (m_camera->Frustum.Intersect(probe->Position, probe->Radius))
			{
				probe->Irradiance->Bind(3);

				CShader* irradianceShader = m_materialLibrary->deferredIrradianceShader;
				irradianceShader->activeShader();
				irradianceShader->SetVector("camPos", m_camera->Position);
				irradianceShader->SetVector("probePos", probe->Position);
				irradianceShader->SetFloat("probeRadius", probe->Radius);
				irradianceShader->SetInt("SSAO", m_postProcess->SSAO);

				glm::mat4 model;
				glm::translate(model, probe->Position);
				glm::scale(model, glm::vec3(probe->Radius));
				irradianceShader->SetMatrix("model", model);

				RenderMesh(m_deferredPointMesh);
			}
		}
		m_glCache.SetCullFace(GL_BACK);
	}
	else
	{
		CShader* ambientShader = m_materialLibrary->deferredAmbientShader;
		ambientShader->activeShader();
		skyCapture->Irradiance->Bind(3);
		skyCapture->PrefilteredMap->Bind(4);
		m_pbrCapture->m_renderTargetBRDFLut->GetColorTexture(0)->Bind(5);
		m_postProcess->SSAOOutput->Bind(6);
		ambientShader->SetInt("SSAO", m_postProcess->SSAO);
		RenderMesh(m_quadNDC);
	}

}

void Renderer::RenderDeferredDirLight(DirectionalLight* light)
{
	CShader* dirShader = m_materialLibrary->deferredDirectionalShader;

	dirShader->activeShader();
	dirShader->SetVector("camPos", m_camera->Position);
	dirShader->SetVector("lightDir", light->Direction);
	dirShader->SetVector("lightColor", glm::normalize(light->Color) * light->Intensity);
	dirShader->SetBool("ShadowsEnabled", enableShadows);

	if (light->ShadowMapRT)
	{
		dirShader->SetMatrix("lightShadowViewProjection", light->LightSpaceViewProjection);
		light->ShadowMapRT->GetDepthStencilTexture()->Bind(3);
	}
	RenderMesh(m_quadNDC);
}

void Renderer::RenderDeferredPointLight(PointLight* light)
{
	CShader* pointShader = m_materialLibrary->deferredPointShader;
	
	pointShader->activeShader();
	pointShader->SetVector("camPos", m_camera->Position);
	pointShader->SetVector("lightPos", light->Position);
	pointShader->SetFloat("lightRadius", light->Radius);
	pointShader->SetVector("lightColor", glm::normalize(light->Color) * light->Intensity);

	glm::mat4 model;
	glm::translate(model, light->Position);
	glm::scale(model, glm::vec3(light->Radius));
	pointShader->SetMatrix("model", model);

	RenderMesh(m_deferredPointMesh);
}

RenderTarget* Renderer::GetCurrentRenderTarget()
{
	return m_currentRenderTarget;
}

void Renderer::RenderShadowCastCommand(RenderCommand* command, const glm::mat4& porj, const glm::mat4& view)
{
	//渲染shadow map阴影
	CShader* shadowShader = m_materialLibrary->dirShadowShader;
	shadowShader->activeShader();
	shadowShader->SetMatrix("projection", porj);
	shadowShader->SetMatrix("view", view);
	shadowShader->SetMatrix("model", command->Transfrom);

	RenderMesh(command->mesh);
}

//将材质粘贴到纹理渲染对象上
void Renderer::Blit(RenderTarget* renderTarget, Material* renderMaterial)
{
	glViewport(0, 0, renderTarget->Width, renderTarget->Height);
	glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->ID);

	//少glClear
	if(renderTarget->hasDepthAndStenCil)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	else
		glClear(GL_COLOR_BUFFER_BIT);
	RenderCommand renderCommand;
	renderCommand.material = renderMaterial;
	renderCommand.mesh = m_quadNDC;
	RenderCustomCommand(&renderCommand, nullptr, true);

}
