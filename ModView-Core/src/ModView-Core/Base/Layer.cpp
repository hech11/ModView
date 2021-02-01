#include "mvpch.h"
#include "Layer.h"

#include <GLFW/include/GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/examples/imgui_impl_opengl3.h>
#include <ImGui/examples/imgui_impl_glfw.h>

#include "ModView-Core/Application.h"



namespace MV {

	// ************ LayerStack ************ //



	LayerStack::~LayerStack() {
		for (auto& layer : m_LayerStack) {
			layer->OnDetach();
			delete layer;
		}

		m_LayerStack.clear();
	}

	void LayerStack::OnUpdate(Timestep dt) {
		for (auto& layer : m_LayerStack) {
			layer->OnUpdate(dt);
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_LayerStack.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
			layer->OnDetach();
			delete layer;
		}

	}

	void LayerStack::PopBackLayer() {
		m_LayerStack.back()->OnDetach();
		delete m_LayerStack.back();
		m_LayerStack.pop_back();
	}


	// ************ ImGuiLayer ************ //


	void ImGuiLayer::OnAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();


		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::GetApp();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow()->GetNativeWindow());


		ImGui_ImplOpenGL3_Init("#version 400");
		ImGui_ImplGlfw_InitForOpenGL(window, true);

	}

	void ImGuiLayer::OnDetach(){
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{

	}

	void ImGuiLayer::OnUpdate(Timestep dt)
	{

	}


	void ImGuiLayer::OnImguiRender() {
	}



	void ImGuiLayer::Start() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::End() {
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Application& app = Application::GetApp();
		io.DisplaySize = ImVec2(app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(context);

		}
	}


}