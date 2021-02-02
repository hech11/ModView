#include "mvpch.h"
#include "Input.h"

#include "ModView-Core/Application.h"
#include <GLFW\include\GLFW\glfw3.h>


namespace MV {



	bool Input::IsKeyPressed(int keycode) {
		auto win = Application::GetApp().GetWindow()->GetNativeWindow();
		return (glfwGetKey(static_cast<GLFWwindow*>(win), keycode) == GLFW_PRESS);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto win = Application::GetApp().GetWindow()->GetNativeWindow();
		return (glfwGetMouseButton(static_cast<GLFWwindow*>(win), button) == GLFW_PRESS);
	}

	std::pair<int, int> Input::GetMousePosition() 
	{
		auto win = Application::GetApp().GetWindow()->GetNativeWindow();

		double x, y;
		glfwGetCursorPos(win, &x, &y);

		return std::make_pair<int, int>((int)x, (int)y);
	}

}