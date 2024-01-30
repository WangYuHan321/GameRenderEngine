#pragma once

#include<vector>
#include<GLM/glm.hpp>

class Renderer;
class RenderTarget;
class Material;
class PBRCapture;
class SceneNode;
class TextureCube;
class CShader;
class Camera;
class Texture;
class Mesh;


class PBR
{
	friend Renderer;
private:
	
	PBRCapture* m_skyCapture = nullptr; //Ìì¿ÕºÐ×Ó
	RenderTarget* m_renderTargetBRDFLut;

	Material* m_pbrHdrToCubeMap;
	Material* m_pbrIrradiance;
	Material* m_pbrPrefilterCapture;
	Material* m_pbrIntegrateBRDF;

	Mesh* m_pbrCaptureCube;
	std::vector<PBRCapture*> m_pbrCaputreProbe;
	SceneNode* m_sceneNode;

	Renderer* m_renderer;

	//probe diffuse
	CShader* m_probeCaptureShader;
	CShader* m_probeCaptureBackgroundShader;
	//probe glass
	Mesh* m_probeDebugSphere;
	CShader* m_probeDebugShader;

public:

	PBR(Renderer* renderer);
	~PBR();

	void SetSkyCapture(PBRCapture* capture);
	//äÖÈ¾Light Probe
	void RenderProbes(Camera& cam);
	void ClearIrradianceProbes();
	void AddIrradianceProbe(PBRCapture* capture, glm::vec3 position, float radius);

	PBRCapture* ProcessEquirectangular(Camera& cam, Texture* envMap);
	PBRCapture* ProcessCubeTest(Camera& cam, TextureCube* capture, bool prefilter = true);
	PBRCapture* ProcessCube(Camera& cam, TextureCube* capture, bool prefilter = true);
	PBRCapture* GetSkyCapture() { return m_skyCapture; }
};

