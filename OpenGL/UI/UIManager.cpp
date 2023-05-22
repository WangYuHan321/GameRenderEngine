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

	ImGui::Columns(3, "hellow", true);

	for(uint32 i =0; i<3; i++)
	{
		ImGui::Button(std::to_string(i).c_str(),ImVec2(200, 40));

		ImGui::SetColumnWidth(40, 200);

		ImGui::NextColumn();
	}
	ImGui::Columns(1);

	ImGui::Columns(3, "hellow1", true);

	for (uint32 i = 0; i < 3; i++)
	{
		ImGui::Button(std::to_string(i).c_str(), ImVec2(200, 40));

		ImGui::SetColumnWidth(40, 200);

		ImGui::NextColumn();
	}
	//ImGui::Begin("Hello, world!");                         

	//ImGui::Text("This is some useful text.");             
	//ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//success


}