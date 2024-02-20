#include "UIManager.h"
#include "Module/Canvas.h"
#include "../../UI/Internel/WidgetContainer.h"
#include "../Editor/Panels/Hierarchy.h"

UIManager::UIManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
	EnableDocking(false);

}

UIManager::~UIManager()
{
}

void UIManager::OnInit(GLFWwindow* p_window, const std::string& p_glslVersion)
{

	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init(p_glslVersion.c_str());

	m_currentCanvas = new Canvas;

	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 0.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 0.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 0.0f;
	style->TabRounding = 0.0f;
	style->ChildRounding = 0.0f;
	style->PopupRounding = 0.0f;

	style->WindowBorderSize = 1.0f;
	style->FrameBorderSize = 0.0f;
	style->PopupBorderSize = 1.0f;

}

void UIManager::OnEnd()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UIManager::EnableDocking(bool p_value)
{
	m_dockingState = p_value;

	if (p_value)
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	else
		ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;
}

void UIManager::Render()
{

	if (m_currentCanvas)
	{
		m_currentCanvas->Draw();
		if(!m_currentCanvas->IsPanelZero())
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

void UIManager::SetCanvas(Canvas& p_canvas)
{
	m_currentCanvas = &p_canvas;
}