#include "mvpch.h"
#include "RenderingContext.h"



#include <GLFW/glfw3.h>
#include <glad.h>
#include <gl/GL.h>

namespace MV {

	void RenderingContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MV_Assert(gladStatus, "Failed to init glad!");

		MV_INFO("OpenGL Info:" << std::endl);
		MV_INFO("Vendor: " << glGetString(GL_VENDOR) << std::endl);
		MV_INFO("Renderer: " << glGetString(GL_RENDERER) << std::endl);
		MV_INFO("Version: " << glGetString(GL_VERSION) << std::endl);

	}

	void RenderingContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}