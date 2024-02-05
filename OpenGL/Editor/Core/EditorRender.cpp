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

void EditorRender::DoRender()
{

}



void EditorRender::RenderScene()
{

}

void EditorRender::RenderUI()
{
	m_context.m_uiMgr->Render();
}