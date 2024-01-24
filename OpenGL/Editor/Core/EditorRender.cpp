#include "EditorRender.h"
#include "Context.h"
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
	m_context.m_renderer->SetCamera(m_context.m_Camera);
	for (int i = 0; i < SceneManager::getInstance()->GetActiveScene()->Root->GetChildCount(); i++)
	{
		m_context.m_renderer->PushRender(SceneManager::getInstance()->GetActiveScene()->Root->GetChildByIndex(i));
	}
	m_context.m_renderer->RenderPushedCommands();
}

void EditorRender::RenderUI()
{
	m_context.m_uiMgr->Render();
}