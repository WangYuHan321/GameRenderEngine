#include "UIManager.h"
#include "Module/Canvas.h"

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
}

void UIManager::OnEnd()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UIManager::SetCanvas(Canvas& p_canvas)
{
	m_currentCanvas = &p_canvas;
}

void UIManager::Render()
{
#if 0 
	if (m_currentCanvas)
	{
		m_currentCanvas->Draw();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

#endif
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


}