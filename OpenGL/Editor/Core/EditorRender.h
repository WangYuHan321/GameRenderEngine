#pragma once

#include "../../Render/Mesh/Material.h"

class Context;
class Camera;

class EditorRender
{



public:
	EditorRender(Context& p_context);

	void InitMaterials();
	void RenderScene();
	void RenderUI();

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



};

