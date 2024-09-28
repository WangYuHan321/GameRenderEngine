#include<stdio.h>
#include "Util/common.h"
#include <glm/gtx/string_cast.hpp>

#ifdef USE_NO_EDITOR
#include "Render/Lighting/DirectionalLight.h"
#include "Render/Lighting/PointLight.h"
#include "Scene/Background.h"
#include "pbr_capture.h"
#include "Util/Utils.h"
#include "UI/Widgets/Button/Button.h"
#include "UI/Widgets/Button/ButtonImage.h"
#include "UI/Panel/PanelMenuBar.h"
#include "UI/Module/Canvas.h"
#include "UI/Widgets/Text/Text.h"
#include "Global/GlobalContext.h"

#else
	#include "Editor/Core/Application.h"
	#include "File/ConfigManager.h"
	#include "Thread/ThreadPool.h"
	#include "File/FileMonitor.h"
#endif

#ifdef USE_NO_EDITOR

GlobalContext* g_pGlobalContext = new GlobalContext();
FlyCamera* cam = new FlyCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

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

	std::vector<PointLight> torchLights;
	{
		PointLight torch;
		torch.Radius = 2.5;
		torch.Color = glm::vec3(1.0f, 0.3f, 0.05f);
		torch.Intensity = 50.0f;
		torch.RenderMesh = true;

		torch.Position = glm::vec3(4.85f, 0.7f, 1.43f);
		torchLights.push_back(torch);
		torch.Position = glm::vec3(4.85f, 0.7f, -2.2f);
		torchLights.push_back(torch);
		torch.Position = glm::vec3(-6.19f, 0.7f, 1.43f);
		torchLights.push_back(torch);
		torch.Position = glm::vec3(-6.19f, 0.7f, -2.2f);
		torchLights.push_back(torch);
		g_pGlobalContext->m_renderer->AddPointLight(&torchLights[0]);
		g_pGlobalContext->m_renderer->AddPointLight(&torchLights[1]);
		g_pGlobalContext->m_renderer->AddPointLight(&torchLights[2]);
		g_pGlobalContext->m_renderer->AddPointLight(&torchLights[3]);
	}

	cam->SetPerspective(Deg2Rad(60.0f),
		g_pGlobalContext->m_renderer->m_renderSize.x / g_pGlobalContext->m_renderer->m_renderSize.y, 0.001f, 100.0f);

	SceneNode* sponza = ResourceManager::getInstance()->LoadMesh(
		"sponza", "Asset\\meshes\\sponza\\sponza.obj");

	sponza->SetPosition(glm::vec3(0.0, -1.0, 0.0));
	sponza->SetScale(0.01f);

	Background* background = new Background(*g_pGlobalContext);
	g_pGlobalContext->m_renderer->InitSkyBox(*cam);
	PBRCapture* p = g_pGlobalContext->m_renderer->GetSkyCapture();
	background->SetCubeMap(p->PrefilteredMap);
	background->Material->SetFloat("lodLevel", 1.5f);

	{
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(0.0f, 0.5f, -0.5f), 3.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(3.0f, 0.5f, -0.5f), 3.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(6.0f, 0.5f, -0.5f), 3.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(8.5f, 0.5f, -0.5f), 3.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(11.4f, 0.5f, -0.5f), 4.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-3.0f, 0.5f, -0.5f), 3.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-6.2f, 0.5f, -0.5f), 3.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-9.5f, 0.5f, -0.5f), 3.25);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-12.1f, 0.5f, -0.5f), 4.25);
		/* bottom floor - left wing*/
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(0.0f, 0.5f, 4.0f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(4.0f, 0.5f, 4.0f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(8.0f, 0.5f, 4.0f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(12.0f, 0.5f, 4.0f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-4.0f, 0.5f, 4.0f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-8.0f, 0.5f, 4.0f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-12.0f, 0.5f, 4.0f), 4.0);
		 //bottom floor - right wing
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(0.0f, 0.5f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(4.0f, 0.5f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(8.0f, 0.5f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(12.0f, 0.5f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-4.0f, 0.5f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-8.0f, 0.5f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-12.0f, 0.5f, -4.5f), 4.0);
	/*	 1st floor - center wing*/
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(0.0f, 5.0f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(4.0f, 5.0f, -0.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(8.0f, 5.0f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(12.0f, 5.0f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-4.0f, 5.0f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-8.0f, 5.0f, -0.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-12.0f, 5.0f, -0.5f), 4.5);
	/*	 1st floor - left wing*/
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(0.0f, 5.0f, 4.0), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(4.0f, 5.0f, 4.0), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(8.0f, 5.0f, 4.0), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(12.0f, 5.0f, 4.0), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-4.0f, 5.0f, 4.0), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-8.0f, 5.0f, 4.0), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-11.5f, 5.0f, 4.0), 4.0);
		 //1st floor - right wing
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(0.0f, 5.0f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(4.0f, 5.0f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(8.0f, 5.0f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(12.0f, 5.0f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-4.0f, 5.0f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-8.0f, 5.0f, -4.5f), 4.0);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-11.5f, 5.0f, -4.5f), 4.0);
		 //2nd floor - center wing
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(0.0f, 9.5f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(4.0f, 9.5f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(8.0f, 9.5f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(12.0f, 9.5f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-4.0f, 9.5f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-8.0f, 9.5f, -0.5f), 4.5);
		g_pGlobalContext->m_renderer->AddIrradianceProbe(glm::vec3(-11.5f, 9.5f, -0.5f), 4.5);

		 //bake before rendering
		g_pGlobalContext->m_renderer->BakeProbes(nullptr, cam);
	}

	g_pGlobalContext->m_window->SetCursorShape(CursorShape::VRESIZE);

	while (!g_pGlobalContext->m_window->ShouldClose())
	{
		g_pGlobalContext->m_device->PollEvents();
		//¼üÅÌÊó±êÊäÈë
		if (g_pGlobalContext->m_inputMgr->IsKeyReleased(EKey::KEY_ESCAPE))
		{
			g_pGlobalContext->m_window->SetShouldClose(true);
			break;
		}

		g_pGlobalContext->m_renderer->Clear();

		g_pGlobalContext->m_timeMgr->Update();

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
				cam->InputMouse(diff.first, diff.second);
				oldDelta = newDelta;
			}
		}

		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_W))
			cam->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_FORWARD);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_S))
			cam->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_BACK);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_A))
			cam->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_LEFT);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_D))
			cam->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_RIGHT);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_E))
			cam->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_UP);
		if (g_pGlobalContext->m_inputMgr->IsKeyPressed(EKey::KEY_F))
			cam->InputKey(g_pGlobalContext->m_timeMgr->GetDeltaTime(), CAMERA_DOWN);
		if (g_pGlobalContext->m_inputMgr->IsKeyReleased(EKey::KEY_F9))
			g_pGlobalContext->m_renderer->enableWireframe = !g_pGlobalContext->m_renderer->enableWireframe;
		if (g_pGlobalContext->m_inputMgr->IsKeyReleased(EKey::KEY_F10))
			g_pGlobalContext->m_renderer->enableDebugGBuffer = !g_pGlobalContext->m_renderer->enableDebugGBuffer;
		if (g_pGlobalContext->m_inputMgr->IsKeyReleased(EKey::KEY_F8))
			g_pGlobalContext->m_renderer->enableIrradianceGI = !g_pGlobalContext->m_renderer->enableIrradianceGI;


		cam->Update(g_pGlobalContext->m_timeMgr->GetDeltaTime());

		g_pGlobalContext->m_renderer->PushRender(background);
		g_pGlobalContext->m_renderer->PushRender(sponza);
		g_pGlobalContext->m_renderer->RenderPushedCommands(*cam);
		
		g_pGlobalContext->m_uiMgr->Render();

		g_pGlobalContext->m_window->SwapBuffer();
		g_pGlobalContext->m_inputMgr->ClearEvents();

	}

	delete g_pGlobalContext;

	return 0;
}

#else

int main()
{ 
	/*
	Quaternion quat1(0.2, 0.3, 0.2, 1.0);
	glm::vec3 vector3(1.2, 1.4, 1.3);

	glm::vec3 q = quat1 * vector3;

	Matrix4 mat1(0.2f, 0.3, 0.1f, 0.0f,
		0.1f, 0.2f, 0.3f, 0.0f,
		0.0f, 0.3f, 0.2f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);

	Matrix4 mat2(0.2f, 0.3, 0.1f, 0.0f,
		0.2f, 0.3f, 0.3f, 0.0f,
		0.1f, 0.2f, 0.3f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);

	Matrix4 mat3(0.2f, 0.3, 0.1f, 0.0f,
		0.3f, 0.4f, 0.5f, 0.0f,
		0.2f, 0.2f, 0.2f, 0.0f,
		0.1f, 0.1f, 0.2f, 0.0f);

	Matrix4 mattt = mat3 * mat2 * mat1;

	printf(" %s ", glm::to_string(mattt).c_str());

	printf("%f %f %f", q.x, q.y, q.z);

	printf("=================================================\n", q.x, q.y, q.z);

	auto scene = new SceneManager();
	scene->LoadEmptyLightedScene();

	for (auto it : scene->GetActiveScene()->GetActors())
	{
		CCamera* pCamera = (CCamera*)it;
		if (it->GetName() == "Main Camera")
		{
			mattt = it->m_transform.GetFTransform().GetLocalMatrix();

			printf(" %s ", glm::to_string(mattt).c_str());


			mattt = it->m_transform.GetFTransform().GetWorldMatrix();

			printf(" %s ", glm::to_string(mattt).c_str());
		}
	}

	Matrix3 mat33(-1.00000000, -2.99003560e-08, -8.21505211e-08,
		- 1.77635620e-15, 0.939692616, -0.342020124,
		8.74227624e-08, -0.342020243, -0.939692616);

	glm::quat qqq = glm::toQuat
	(mat33);

	printf("---------------------------------------------------------------------------------------------------\n");
	printf("%s", glm::to_string(qqq).c_str());
	return 0;
	*/

	Application app("", "");
	
	FileMonitor* ptest = new FileMonitor();
	ptest->SetDirectory(ConfigManager::getInstance()->GetEnginePath());
	ThreadPool::getInstance()->AddTask( std::unique_ptr<IRunable>(ptest) );

	while (app.IsRunning())
	{
		app.Run();
	}
	checkForMemoryLeaks();
}

#endif

//#include "RHI/RHIVulkan.h"
//
//int main()
//{
//	RHIVulkan rhiVulkan;
//
//	rhiVulkan.InitWindow();
//	rhiVulkan.InitVulkan();
//	rhiVulkan.MainLoop();
//
//}







