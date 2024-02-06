#pragma once

class RenderTarget;

#include "BaseRenderer.h"
#include "GLCache.h"
#include "Setting/EPrimitiveMode.h"

class Scene;
class Mesh;
class Material;
class Frustum;

struct FrameInfo
{
	uint64_t batchCount = 0;
	uint64_t instanceCount = 0;
	uint64_t polyCount = 0;
};

class ForwardRenderer :
    public BaseRenderer
{
public:

	using Drawable = std::tuple<Matrix4, Mesh*, Material*, Matrix4>;
	using OpaqueDrawables = std::multimap<float, Drawable, std::less<float>>;
	using TransparentDrawables = std::multimap<float, Drawable, std::greater<float>>;

	ForwardRenderer();
	~ForwardRenderer();

	virtual void DoRender() ;
	virtual void OnReSize(uint32 width, uint32 height);
	virtual void Initialize() ;
	virtual void Clear() ;


	void RenderScene(Scene& p_scene,
		const Vector3& p_cameraPosition,
		const Camera& p_camera,
		const Frustum* p_customFrustum,
		Material* p_defaultMaterial);


	std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortDRawables(const Scene& p_scene, const Vector3 p_camPos, Material* p_defaultMaterial);

	void DrawDrawable(const Drawable& p_toDraw);

	void DrawMesh(Mesh& p_mesh, Material& p_material, Matrix4 p_mat4);

	void Draw(Mesh& p_mesh, EPrimitiveMode model, uint32 drawNumObj);

	void Clear(bool p_colorBuffer = true, bool p_deptBuffer = true, bool p_stencilColor = true);

	void ApplyStateMask(uint8_t mask);

	void SetState(uint8_t p_state);
	
private:
	std::function<void(Matrix4)> m_modelMatrixSender;
	std::function<void(Matrix4)> m_userMatrixSender;
	RenderTarget* m_renderTarget;

	GLCache m_glCache;
	uint8_t				m_state;
	FrameInfo m_frameInfo;
};

