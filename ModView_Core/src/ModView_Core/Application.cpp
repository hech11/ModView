#include "mvpch.h"
#include "Application.h"
#include "Base/Base.h"

#include <GLFW/include/GLFW/glfw3.h>
#include <GLAD/include/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderCommand.h"

namespace MV {

	Application* Application::s_Instance = nullptr;



	Application::Application() {
		MV_Assert(!s_Instance, "There already is an instance of application!");
		s_Instance = this;

		m_Window = Scoped<Window>(new Window({}));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_Window->SetVSync(true);


		m_ImGuiLayer = new ImGuiLayer;
		PushLayer(m_ImGuiLayer);

		m_IsRunning = true;
	}

	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer) {
		m_LayerStack.PopLayer(layer);
	}
	void Application::PopBackLayer() {
		m_LayerStack.PopBackLayer();
	}


	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(MV_BIND_EVENT_FUNC(Application::OnWindowClose));

		for (auto& layer : m_LayerStack.GetLayerStack()) {
			layer->OnEvent(e);
			if (e.Handled)
				break;
		}
	}




	void Application::Run() {


		while (m_IsRunning) {
			auto time = (float)glfwGetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;


			RenderCommand::Clear();

			for (auto& layer : m_LayerStack.GetLayerStack()) {
				layer->OnUpdate(ts);
			}



			m_ImGuiLayer->Start();
			for (auto& layer : m_LayerStack.GetLayerStack()) {
				layer->OnImguiRender();
			}
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowClosedEvent& e) {
		m_IsRunning = false;
		return true;
	}



}

