#include "mvpch.h"
#include "Application.h"


namespace MV {

	Application* Application::s_Instance = nullptr;



	Application::Application() {
		MV_Assert(!s_Instance);
		s_Instance = this;
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e)
	{

	}


	void Application::Run() {
		while(true);
	}

}

