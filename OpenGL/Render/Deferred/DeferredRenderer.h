#pragma once
#include "../BaseRenderer.h"

class RenderTarget;
class Material;
class Texture;
class CShader;
class Mesh;
class Scene;

class DeferredRenderer : public BaseRenderer
{
	using Drawable = std::tuple<Matrix4, Mesh*, Material*, Matrix4>;
	using OpaqueDrawables = std::multimap<float, Drawable, std::less<float>>;
	using TransparentDrawables = std::multimap<float, Drawable, std::greater<float>>;

public:
	DeferredRenderer();
	~DeferredRenderer();

	void Initialize();
	virtual void DoRender() override;
	virtual void OnReSize(uint32 width, uint32 height) override;

	void RenderScene(Scene& pScene, Camera& pCamera, Vector3& pCameraPos, Material* pDefaultMat);

private:
	std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortDRawables(const Scene& p_scene, const Vector3 p_camPos, Material* p_defaultMaterial);

	void DrawDrawable(const Drawable& p_toDraw);
	void Draw(Mesh& p_mesh, uint32 drawNumObj);
private:
	RenderTarget* m_renderGBuffer;

	Texture* m_gBufferInfo;
	Texture* m_gBufferDepth;

	CShader* m_gBufferShader;
};

