#pragma once

class RenderTarget;

#include "BaseRenderer.h"

class Scene;
class Mesh;
class Material;
class Frustum;

class ForwardRenderer :
    public BaseRenderer
{
public:

	using Drawable = std::tuple<Matrix4, Mesh*, Material*, Matrix4>;
	using OpaqueDrawables = std::multimap<float, Drawable, std::less<float>>;
	using TransparentDrawables = std::multimap<float, Drawable, std::greater<float>>;

	virtual void DoRender() ;
	virtual void OnReSize(uint32 width, uint32 height);
	virtual void Initialize() ;
	virtual void Clear() ;

protected:

	void RenderScene(Scene& p_scene,
		const Vector3& p_cameraPosition,
		const Camera& p_camera,
		const Frustum* p_customFrustum,
		Material* p_defaultMaterial);


	std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortDRawables(const Scene& p_scene, const Vector3 p_camPos, const Material& p_defaultMaterial);

	void DrawDrawable(const Drawable& p_toDraw);

	void DrawMesh(Mesh& p_mesh, Material& p_material, Matrix4 p_mat4);

	void Clear(bool p_colorBuffer = true, bool p_deptBuffer = true, bool p_stencilColor = true);
	
private:
	RenderTarget* renderTarget;
};

