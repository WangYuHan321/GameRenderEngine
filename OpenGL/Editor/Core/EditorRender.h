#pragma once

#include "../../Render/Mesh/Material.h"
#include "../../Render/ForwardRenderer.h"
#include "../../Editor/Core/GizmoBehaviour.h"

class Context;
class Camera;
class Actor;

class EditorRender : ForwardRenderer
{



public:
	EditorRender(Context& p_context);
	~EditorRender();

	void InitMaterials();
	void RenderScene(const Vector3& p_cameraPos, const Camera& p_camera);
	void RenderUI();

	void RenderGrid(Vector3& p_viewPos, Vector3& p_color);
	void RenderSceneForActorPicking();
	void RenderGizmo(Vector3& p_pos, Quaternion& p_quat, EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis = -1);

	void RenderCameras();
	Matrix4 CalculateCameraModelMatrix(Actor& actor);

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

