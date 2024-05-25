#pragma once

#include "../../Render/Mesh/Material.h"
#include "../../Render/Forward/ForwardRenderer.h"
#include "../../Editor/Core/GizmoBehaviour.h"

class Context;
class Camera;
class Actor;
class CCamera;
class ShapeDrawer;

class EditorRender : ForwardRenderer
{



public:
	EditorRender(Context& p_context);
	~EditorRender();

	void InitMaterials();
	void PreparePickingMaterial(Actor& p_actor, Material& p_material);
	void RenderScene(const Vector3& p_cameraPos, const Camera& p_camera);
	void RenderUI();

	void RenderGrid(Vector3& p_viewPos, Vector3& p_color);
	void RenderSceneForActorPicking();
	void RenderModelToStencil(Matrix4& p_worldMatrix, Model& p_model);
	void RenderModelOutline(Matrix4& p_worldMatrix, Model& p_model, float p_width);
	void RenderActorOutlinePass(Actor& p_actor, bool p_toStencil, bool p_isSelected);
	void RenderActor(Actor& p_actor);
	void RenderLights();
	void RenderCameraFrustum(CCamera& p_camera);
	void RenderMaterialAsset(Material& p_material);
	void RenderCameraPerspectiveFrustum(std::pair<uint16_t, uint16_t> p_size, CCamera& p_camera);
	void RenderCameraOrthographicFrustum(std::pair<uint16_t, uint16_t>& p_size, CCamera& p_camera);
	void DebugRenderOrthographicFrustum(const Vector3& pos, const Vector3& forward, float nearPanel, const float farPanel, const Vector3& a,
		const Vector3& b, const Vector3& c, const Vector3& d);

	void RenderGizmo(Vector3& p_pos, Quaternion& p_quat, EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis = -1);
	void DrawFrustumLines(ShapeDrawer& p_drawer,const Vector3& pos,const Vector3& forward,float nearPanel,const float farPanel,const Vector3& a,
		const Vector3& b,const Vector3& c,const Vector3& d,const Vector3& e,const Vector3& f,const Vector3& g,const Vector3& h);

	void RenderCameras();
	Matrix4 CalculateCameraModelMatrix(Actor& actor);

	void UpdateLights(Scene& p_scene);

	virtual void DoRender();

private:

	Camera* m_camera;
	Context& m_context;

	Material m_gridMaterial;
	Material m_stencilFillMaerial;
	Material m_textureMaterial;
	Material m_outlineMaterial;
	Material m_emptyMaterial;
	Material m_defaultMaterial;
	Material m_cameraMaterial;
	Material m_lightMaterial;
	Material m_gizmoArrowMaterial;
	Material m_gizmoBallMaterial;
	Material m_gizmoPickingMaterial;
	Material m_actorPickingMaterial;

	Texture* m_pTexture;

};

