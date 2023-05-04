
#if 0
#include "GLFWWindow.h"

#include "../Render/Renderer.h"
#include "../Camera/Camera.h"

void FramebufferSizeFunc(GLFWwindow* window, int width, int height)
{

}

void KeyFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void MousePosFunc(GLFWwindow* window, double xpos, double ypos)
{

}

void MouseButtonFunc(GLFWwindow* window, int button, int action, int mods)
{

}

void MouseScrollFunc(GLFWwindow* window, double xoffset, double yoffset)
{

}

//auto f = std::bind(&A::func, this, std::placeholders::_1);
//std::function<void(int)> fun(f);
//void (*pfun)(int) = fun.target<void(int)>();
void GLFWWindow::init()
{
	//GLFW 初始化步骤 glfw 4.3 version
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// use multiisample
	//glfwWindowHint(GLFW_SAMPLES, 4); 使用4x MSAA
	glfwWindowHint(GLFW_SAMPLES, MSAA_NUM); // 使用4x MSAA

	m_pWinwdow = glfwCreateWindow(GWindowInfo.WINDOW_WIDTH, GWindowInfo.WINDOW_HEIGHT, GWindowInfo.WINDOW_TITLE.c_str(), nullptr, nullptr);
	if (!m_pWinwdow)
	{
		GTipWindowLog.OutputError("Error:::Window Create Faile!!!\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_pWinwdow);
	if (GInputModel.INPUT_CURSOUR_DISABLE)
		glfwSetInputMode(m_pWinwdow, GLFW_CURSOR, GInputModel.INPUT_CURSOUR_DISABLE);

	glewExperimental = true;
	if (glewInit()!= GLEW_OK)
	{
		GTipWindowLog.OutputError("Error:::Window GLEW Init Faile!!!\n");
		return;
	}

	glfwSetFramebufferSizeCallback(m_pWinwdow, &FramebufferSizeFunc); 
	glfwSetKeyCallback(m_pWinwdow, &KeyFunc);
	glfwSetCursorPosCallback(m_pWinwdow, &MousePosFunc);
	glfwSetMouseButtonCallback(m_pWinwdow, &MouseButtonFunc);
	glfwSetScrollCallback(m_pWinwdow, &MouseScrollFunc);

	m_pCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void GLFWWindow::Run(Renderer* render)
{
	while (!glfwWindowShouldClose(m_pWinwdow))
	{
		render->RenderPushedCommands();
		m_pCamera->Update(0.1f);
		glfwSwapBuffers(m_pWinwdow);
	}
}

void GLFWWindow::Close()
{
	glfwTerminate();
}

GLFWwindow* GLFWWindow::getWindow() const
{
	return m_pWinwdow;
}


#endif