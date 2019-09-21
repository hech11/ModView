#include "ModView_Core.h"
#include "ImGui/imgui.h"


class ApplicationLayer : public MV::Layer {

	public :
		ApplicationLayer() : Layer("Application Layer") { }

		void OnAttach() override {
		}
		void OnDetach() override {
		}

		void OnEvent(MV::Event& e) override {


		}
		void OnUpdate(MV::Timestep dt) override {
		}


		void OnImguiRender() override {
			ImGui::Begin("Sandbox test!");
			ImGui::End();
		}


	private :
};

class Sandbox : public MV::Application {


	public :

		Sandbox() {
			PushLayer(new ApplicationLayer);
		}
		~Sandbox() {}

};



MV::Application* MV::CreateApplication() {
	return new Sandbox();
}
