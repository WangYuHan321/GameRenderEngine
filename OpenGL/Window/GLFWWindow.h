
#if 0 
#pragma once
#include "../Util/common.h"
#include "../Util/Singleton.h"

class Renderer;
class Camera;


class GLFWWindow : public CSingleton<GLFWWindow>
{
public:

	void init();
	void Run(Renderer * render);
	void Close();

	//void FramebufferSizeFunc(GLFWwindow* window, int width, int height);
	//void KeyFunc(GLFWwindow* window, int key, int scancode, int action, int mods);
	//void MousePosFunc(GLFWwindow* window, double xpos, double ypos);
	//void MouseButtonFunc(GLFWwindow*, int button, int action, int mods);
	//void MouseScrollFunc(GLFWwindow*, double xoffset, double yoffset);

	GLFWwindow* getWindow() const;

private:
	GLFWwindow* m_pWinwdow;
	Camera* m_pCamera;
};

#endif