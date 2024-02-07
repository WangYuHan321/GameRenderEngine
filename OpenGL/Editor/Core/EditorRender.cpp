#include "EditorRender.h"
#include "Context.h"
#include <memory.h>
#include "../../Camera/Camera.h"
#include "../../Scene/SceneManager.h"


EditorRender::EditorRender(Context& p_context):
	m_context(p_context)
{
	InitMaterials();
}

void EditorRender::InitMaterials()
{


}

void EditorRender::DoRender()
{

}



void EditorRender::RenderScene(const Vector3& p_cameraPos, const Camera& p_camera)
{
	dynamic_cast<ForwardRenderer*>(m_context.m_renderer.get())->RenderScene(*m_context.m_sceneMgr->GetActiveScene(), p_cameraPos, p_camera, nullptr, &m_emptyMaterial);
}

void EditorRender::RenderUI()
{
	m_context.m_uiMgr->Render();
}