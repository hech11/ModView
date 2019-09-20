#include "mvpch.h"
#include "Application.h"


namespace MV {

	Application* Application::s_Instance = nullptr;



	Application::Application() {
		MV_Assert(!s_Instance);
		s_Instance = this;

		m_Window = Scoped<Window>(new Window({}));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e) {
		std::cout << e.ToString() << std::endl;
	}


	void Application::Run() {
		while (true) {


			m_Window->OnUpdate();
		}
	}

}

