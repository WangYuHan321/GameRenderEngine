#include "Canvas.h"
#include "../../ThirdLib/ImGui/imgui.h"
#include "../../ThirdLib/ImGui/imgui_internal.h"
#include "../../ThirdLib/ImGui/imgui_impl_glfw.h"
#include "../../ThirdLib/ImGui/imgui_impl_opengl3.h"


void Canvas::AddPanel(APanel& p_panel)
{
	m_panels.push_back(std::ref(p_panel));
}

void Canvas::Draw()
{
	if (!m_panels.empty())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

	/*	if (m_isDockspace)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::Begin("##dockspace", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
			ImGui::SetWindowPos({ 0.f, 0.f });
			ImVec2 displaySize = ImGui::GetIO().DisplaySize;
			ImGui::SetWindowSize({ (float)displaySize.x, (float)displaySize.y });
			ImGui::End();

			ImGui::PopStyleVar(3);
		}*/

		//Profilter panelwindow 没有重写draw方法会报错
		for (auto& panel : m_panels)
			panel.get().Draw();

		ImGui::Render();
		ImGui::EndFrame();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}