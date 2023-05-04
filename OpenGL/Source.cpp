#include<stdio.h>
#include "Render/Lighting/DirectionalLight.h"
#include "Util/Utils.h"
#include "Global/GlobalContext.h"

GlobalContext* g_pGlobalContext = new GlobalContext();

std::pair<double, double> oldDelta;
std::pair<double, double> newDelta;
bool isFirst = true;

int main()
{
	DirectionalLight dirLight;
	dirLight.Direction = glm::vec3(0.2f, -1.0f, 0.25f);	
	dirLight.Color = glm::vec3(1.0f, 0.89f, 0.7f);
	dirLight.Intensity = 50.0f;
	g_pGlobalContext->m_renderer->AddDirLight(&dirLight);

	g_pGlobalContext->m_Camera->SetPerspective(Deg2Rad(60.0f), 
		g_pGlobalContext->m_renderer->m_renderSize.x / g_pGlobalContext->m_renderer->m_renderSize.y, 0.1f, 100.0f);
	g_pGlobalContext->m_renderer->SetCamera(g_pGlobalContext->m_Camera);

	SceneNode* sponza = ResourceManager::getInstance()->LoadMesh(
		"sponza", "Asset\\meshes\\sponza\\sponza.obj");

	sponza->SetPosition(glm::vec3(0.0, -1.0, 0.0));
	sponza->SetScale(0.01f);

	//g_pGlobalContext->m_window->SetCursorShape(CursorShape::CROSSHAIR);

	while (!g_pGlobalContext->m_window->ShouldClose())
	{
		g_pGlobalContext->m_device->PollEvents();
		g_pGlobalContext->m_timeMgr->Update();

		//¼üÅÌÊó±êÊäÈë

		if (g_pGlobalContext->m_inputMgr->IsKeyReleased(EKey::KEY_ESCAPE))
		{
			g_pGlobalContext->m_window->SetShouldClose(true);
		}

		if (g_pGlobalContext->m_inputMgr->IsMouseButtonReleased(EMouseButton::MOUSE_BUTTON_RIGHT))
		{
			oldDelta = newDelta = { 0.0f,0.0f };
			isFirst = true;
		}

		if (g_pGlobalContext->m_inputMgr->IsMouseButtonPressed(EMouseButton::MOUSE_BUTTON_RIGHT))
		{
			if (isFirst)
			{
				newDelta = g_pGlobalContext->m_inputMgr->GetMousePosition();
				oldDelta = newDelta;
				isFirst = false;
			}
			else
			{
				newDelta = g_pGlobalContext->m_inputMgr->GetMousePosition();
				std::pair<double, double>  diff = { oldDelta.first - newDelta.first,
					oldDelta.second - newDelta.second };
				g_pGlobalContext->m_Camera->InputMouse(diff.first, diff.second);
				oldDelta = newDelta;
			}
		}

		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_W))
			g_pGlobalContext->m_Camera->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_FORWARD);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_S))
			g_pGlobalContext->m_Camera->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_BACK);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_A))
			g_pGlobalContext->m_Camera->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_LEFT);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_D))
			g_pGlobalContext->m_Camera->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_RIGHT);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_E))
			g_pGlobalContext->m_Camera->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_UP);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_F))
			g_pGlobalContext->m_Camera->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_DOWN);

		g_pGlobalContext->m_Camera->Update(g_pGlobalContext->m_timeMgr->GetDeltaTime());

		g_pGlobalContext->m_renderer->PushRender(sponza);
		g_pGlobalContext->m_renderer->RenderPushedCommands();
		
		g_pGlobalContext->m_window->SwapBuffer();
		g_pGlobalContext->m_inputMgr->ClearEvents();
	}

	delete g_pGlobalContext;

	return 0;
}