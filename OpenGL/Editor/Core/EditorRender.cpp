#include "EditorRender.h"
#include "Context.h"
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

void EditorRender::RenderScene()
{
	for (int i = 0; i < m_context.m_sceneMgr->GetActiveScene()->Root->GetChildCount(); i++)
	{
		/*m_context.m_renderer->PushRender(m_context.m_sceneMgr->GetActiveScene()->Root->GetChildByIndex(i), m_camera);*/
	}
	/*m_context.m_renderer->RenderPushedCommands(m_camera);*/
}

void EditorRender::RenderUI()
{
	m_context.m_uiMgr->Render();
}