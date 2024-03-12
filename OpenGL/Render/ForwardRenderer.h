#pragma once

class RenderTarget;

#include "BaseRenderer.h"
#include "GLCache.h"
#include "Setting/EPrimitiveMode.h"
#include "../Render/Shadow/CascadeShadowMap.h"

class Scene;
class Mesh;
class Model;
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
	virtual void SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height) ;
	virtual void Initialize() ;


	void SetRasterizationModel(GLenum model);
	void SetRasterizationLineWidth(float p_lineWidth);
	void SetCapability(GLenum model, bool p_value);
	void SetStencilOperations(GLenum operation, GLenum depthFail, GLenum bothPass);
	void SetStencilAlgorithm(GLenum operation, int32_t value, uint32_t mask);
	void SetStencilMask(uint32_t p_mask);

	void RenderScene(Scene& p_scene,
		const Vector3& p_cameraPosition,
		const Camera& p_camera,
		const Frustum* p_customFrustum,
		Material* p_defaultMaterial);


	std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortDRawables(const Scene& p_scene, const Vector3 p_camPos, Material* p_defaultMaterial);

	void DrawDrawable(const Drawable& p_toDraw);

	void DrawModelWithSingleMaterial(Model& p_model, Material& p_material, Matrix4* p_modelMat, Material* p_defaultMaterial = nullptr);

	void DrawMesh(Mesh& p_mesh, Material& p_material, Matrix4* p_mat4);

	void Draw(Mesh& p_mesh, EPrimitiveMode model, uint32 drawNumObj);

	void Clear(bool p_colorBuffer = true, bool p_deptBuffer = true, bool p_stencilColor = true);

	void ApplyStateMask(uint8_t mask);

	void SetState(uint8_t p_state);

	uint8_t FetchGLState();

	void SetDepthTest(bool val);

	void RegisterModelMatrixSender(std::function<void(Matrix4)> p_modelMatrixSender);

	void RegisterUserMatrixSender(std::function<void(Matrix4)> p_userMatrixSender);

	void ReadPixels(uint32_t x, uint32_t y, uint32_t width, uint32_t height, GLenum format, GLenum type, void* data);

	
	std::vector<Matrix4> GetFindLightMatrices(const Scene& p_scene);
	
private:
	std::function<void(Matrix4)> m_modelMatrixSender;
	std::function<void(Matrix4)> m_userMatrixSender;
	RenderTarget* m_renderTarget;

	GLCache m_glCache;
	uint8_t				m_state;
	FrameInfo m_frameInfo;
};

