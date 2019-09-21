#include "mvpch.h"
#include "Application.h"
#include "Base/Base.h"

#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>

#include "Renderer/Buffer.h"


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

		float vertex[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);


		VertexBuffer vbo;
		vbo.Bind();
		vbo.Resize(sizeof(vertex));
		vbo.UploadData(vertex);



		unsigned char indicies[] = {
			0, 1, 2,
			2, 3, 0
		};
		IndexBuffer ibo(6, IndexBuffer::BufferType::Char);
		ibo.Bind();
		ibo.UploadData(indicies);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glm::vec2 test = {1.0f, 1.0f};
		
		MV_INFO("Vector: " << test.x << ", " << test.y << std::endl);

		while (m_IsRunning) {
			auto time = (float)glfwGetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto& layer : m_LayerStack.GetLayerStack()) {
				layer->OnUpdate(ts);
			}

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);


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

