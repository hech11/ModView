#include "mvpch.h"
#include "Window.h"

#include <GLFW/glfw3.h>

#include "Base.h"

#include "ModView_Core/Event/InputEvents.h"
#include "ModView_Core/Event/WindowEvents.h"


namespace MV {



	void Window::StartUp(const WinProps& props) {

		m_WinData.props = props;
		int glfwValidation = glfwInit();
		MV_Assert(glfwValidation, "Failed to init GLFW!");

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		MV_Assert(m_Window, "Failed to init create a window!");

		SetVSync(false);
		glfwSetWindowPos(m_Window, props.xPos, props.yPos);
		glfwSetWindowUserPointer(m_Window, &m_WinData);


		m_Context = new RenderingContext(m_Window);
		m_Context->Init();


		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			WindowResizeEvent e(width, height);
			data.props.Width = width;
			data.props.Height = height;


			data.EventCallback(e);

		});



		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			WindowClosedEvent e;

			data.EventCallback(e);

		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos) {
			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			WindowMovedEvent e(xpos, ypos);
			data.props.xPos = xpos;
			data.props.yPos = ypos;

			data.EventCallback(e);

		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			if (focused) {
				WindowGainedFocusEvent e;
				data.EventCallback(e);
			} else {
				WindowLostFocusEvent e;
				data.EventCallback(e);
			}

		});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			switch (action) {

				case GLFW_PRESS :
				{
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}

			}

		});


		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float)xpos, (float)ypos);
			data.EventCallback(e);

		});


		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xscroll, double yscroll) {
			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)xscroll, (float)yscroll);
			data.EventCallback(e);

		});


		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

			switch (action) {

				case GLFW_PRESS :
				{
					MouseButtonPressedEvent e(button, 0);
					data.EventCallback(e);
					break;
				}

				case GLFW_REPEAT:
				{
					MouseButtonPressedEvent e(button, 1);
					data.EventCallback(e);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}

			}

		});

	}

	void Window::ShutDown() {
		delete m_Context;
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::OnUpdate() {
		m_Context->SwapBuffers();
		glfwPollEvents();
	}

	void Window::SetTitle(std::string& title) {
		glfwSetWindowTitle(m_Window, title.c_str());
		m_WinData.props.Title = title;
	}

	void Window::SetVSync(bool enable) {
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_WinData.vSync = enable;
	}

	

}