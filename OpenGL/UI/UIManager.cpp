#include "UIManager.h"
#include "Module/Canvas.h"
#include "../Editor/Panels/Hierarchy.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::OnInit(GLFWwindow* p_window, const std::string& p_glslVersion)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	/* Disable moving windows by dragging another thing than the title bar */
	//ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init(p_glslVersion.c_str());
	ImGui::StyleColorsDark();

	m_currentCanvas = new Canvas;

	PanelWindowSetting set;
	m_testPanel = new Hierarchy("test", true, set);
	m_currentCanvas->AddPanel(*m_testPanel);
}

void UIManager::OnEnd()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UIManager::Render()
{

	if (m_currentCanvas)
	{
		m_currentCanvas->Draw();
	}

#if 0
	//success
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("control");
	ImGui::Text("W S A D forward back left right");
	ImGui::TextUnformatted("E F up down");
	ImGui::TextUnformatted("F9 draw wireframe");
	ImGui::TextUnformatted("F8 irradiancGI");
	ImGui::End();

	ImGui::Render();
	ImGui::EndFrame();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//success
#endif


}