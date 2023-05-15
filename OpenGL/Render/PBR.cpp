#include "PBR.h"
#include "Renderer.h"
#include "RenderTarget.h"
#include "Mesh/Material.h"
#include "Mesh/Cube.h"
#include "Mesh/Sphere.h"
#include "../pbr_capture.h"
#include "../Camera/Camera.h"
#include "Resource/ResourceManager.h"

PBR::PBR(Renderer* renderer)
{
	// IBL part
	m_renderer = renderer;
	m_renderTargetBRDFLut = new RenderTarget(128, 128, GL_HALF_FLOAT, 1, true);
	
	CShader * hdrCube = ResourceManager::getInstance()->LoadShader("pbr_HdrToCube", 
		"Shader\\pbr\\cube_sample.vs", "Shader\\pbr\\spherical_to_cube.fs");
	CShader* irradiance = ResourceManager::getInstance()->LoadShader("pbr_Irradiance",
		"Shader\\pbr\\cube_sample.vs", "Shader\\pbr\\irradiance_capture.fs");
	CShader* prefilterCapture = ResourceManager::getInstance()->LoadShader("pbr_PrefilterCapture",
		"Shader\\pbr\\cube_sample.vs", "Shader\\pbr\\prefilter_capture.fs"); 
	CShader* integrateBrdf = ResourceManager::getInstance()->LoadShader("pbr_IntegrateBRDF", 
		"Shader\\scene\\screen_quad.vs", "Shader\\pbr\\integrate_brdf.fs");

	m_pbrHdrToCubeMap = ResourceManager::getInstance()->LoadMaterial("pbr_HdrToCube", hdrCube);
	m_pbrIrradiance = ResourceManager::getInstance()->LoadMaterial("pbr_Irradiance", irradiance);
	m_pbrPrefilterCapture = ResourceManager::getInstance()->LoadMaterial("pbr_PrefilterCapture", prefilterCapture);
	m_pbrIntegrateBRDF = ResourceManager::getInstance()->LoadMaterial("pbr_IntegrateBRDF", integrateBrdf);

	m_pbrHdrToCubeMap->DepthCompare = GL_LEQUAL;
	m_pbrIrradiance->DepthCompare = GL_LEQUAL;
	m_pbrPrefilterCapture->DepthCompare = GL_LEQUAL;

	m_pbrHdrToCubeMap->Cull = false;
	m_pbrIrradiance->Cull = false;
	m_pbrPrefilterCapture->Cull = false;

	m_pbrCaptureCube = new Cube();
	m_sceneNode = new SceneNode(0);
	m_sceneNode->Mesh = m_pbrCaptureCube;
	m_sceneNode->Material = m_pbrHdrToCubeMap;

	//计算Lut 保存在 m_renderTargetBRDFLut
	m_renderer->Blit(m_renderTargetBRDFLut, m_pbrIntegrateBRDF);

	//IBL part

	//capture probe
	// 只计算直接光照 diffuse part
	m_probeCaptureShader = ResourceManager::getInstance()->LoadShader
	("pbr_capture", "Shader\\capture.vs", "Shader\\capture.fs");
	m_probeCaptureShader->activeShader();
	m_probeCaptureShader->SetInt("TexAlbedo", 0);
	m_probeCaptureShader->SetInt("TexNormal", 1);
	m_probeCaptureShader->SetInt("TexMetallic", 2);
	m_probeCaptureShader->SetInt("TexRoughness", 3);

	m_probeCaptureBackgroundShader = ResourceManager::getInstance()->LoadShader
	("pbr_captureBackground", "Shader\\capture_background.vs", "Shader\\capture_background.fs");
	m_probeCaptureBackgroundShader->activeShader();
	m_probeCaptureBackgroundShader->SetInt("background", 0);


	//glass part
	m_probeDebugSphere = new Sphere(32, 32);
	m_probeDebugShader = ResourceManager::getInstance()->LoadShader
	("pbr_probeRender", "Shader\\pbr\\probe_render.vs", "Shader\\pbr\\probe_render.fs");
}

PBRCapture* PBR::ProcessEquirectangular(Texture* envMap)
{
	// 平面坐标系转球坐标系
	m_sceneNode->Material = m_pbrHdrToCubeMap;
	m_pbrHdrToCubeMap->SetTexture("environment", envMap, 0);
	TextureCube hdrEnvMap;
	hdrEnvMap.DefaultInitialize(128, 128, GL_RGB, GL_FLOAT);
	m_renderer->RenderToCubeMap(m_sceneNode, &hdrEnvMap);
	return ProcessCube(&hdrEnvMap);
}

PBRCapture* PBR::ProcessCube(TextureCube* capture, bool prefilter)
{
	PBRCapture* captureProbe = nullptr;
	if (m_skyCapture != nullptr)
		captureProbe = m_skyCapture;
	else
	{
		captureProbe = new PBRCapture;
		captureProbe->Irradiance = new TextureCube;
		captureProbe->PrefilteredMap = new TextureCube;
	}
	//辐照图

	captureProbe->Irradiance->DefaultInitialize(32, 32, GL_RGB, GL_FLOAT);
	m_pbrIrradiance->SetTextureCube("environment", capture, 0);
	m_sceneNode->Material = m_pbrIrradiance;
	m_renderer->RenderToCubeMap(m_sceneNode, captureProbe->Irradiance, 0);
	
	//模糊图
	if (prefilter)
	{
		captureProbe->PrefilteredMap->FilterMin = GL_LINEAR_MIPMAP_LINEAR;
		captureProbe->PrefilteredMap->DefaultInitialize(128, 128, GL_RGB, GL_FLOAT, true);
		
		m_pbrPrefilterCapture->SetTextureCube("environment", capture, 0);
		m_sceneNode->Material = m_pbrPrefilterCapture;
		// calculate prefilter for multiple roughness levels
		unsigned int maxMipLevels = 5;
		for (unsigned int i = 0; i < maxMipLevels; ++i)
		{
			m_pbrPrefilterCapture->SetFloat("roughness", (float)i / (float)(maxMipLevels - 1));
			m_renderer->RenderToCubeMap(m_sceneNode, captureProbe->PrefilteredMap, i);
		}
	}
	return captureProbe;
}

void PBR::SetSkyCapture(PBRCapture* capture)
{
	m_skyCapture = capture;
}

void PBR::RenderProbes()
{
	//首先把镜面反射的贴图
	m_probeDebugShader->activeShader();
	m_probeDebugShader->SetMatrix("projection", m_renderer->GetCamera()->Projection);
	m_probeDebugShader->SetMatrix("view", m_renderer->GetCamera()->View);
	m_probeDebugShader->SetVector("CamPos", m_renderer->GetCamera()->Position);

	m_probeDebugShader->SetVector("Position", glm::vec3(0.0f, 2.0f, 0.0f));
	m_skyCapture->PrefilteredMap->Bind(0);
	m_probeDebugShader->activeShader();
	m_renderer->RenderMesh(m_probeDebugSphere);

	for (int i = 0; i < m_pbrCaputreProbe.size(); ++i)
	{
		m_probeDebugShader->SetVector("Position", m_pbrCaputreProbe[i]->Position);
		if (m_pbrCaputreProbe[i]->PrefilteredMap)
			m_pbrCaputreProbe[i]->PrefilteredMap->Bind(0);
		else
			m_pbrCaputreProbe[i]->Irradiance->Bind(0);
		m_probeDebugShader->activeShader();
		m_renderer->RenderMesh(m_probeDebugSphere);
	}
}

void PBR::AddIrradianceProbe(PBRCapture* capture, glm::vec3 position, float radius)
{
	capture->Position = position;
	capture->Radius = radius;
	m_pbrCaputreProbe.push_back(capture);
}

PBR::~PBR()
{

	for (int i = 0; i < m_pbrCaputreProbe.size(); ++i)
	{
		delete m_pbrCaputreProbe[i]->Irradiance;
		delete m_pbrCaputreProbe[i]->PrefilteredMap;
		delete m_pbrCaputreProbe[i];
	}

	delete m_probeDebugSphere;
	delete m_pbrCaptureCube;
}