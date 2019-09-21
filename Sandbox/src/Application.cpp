#include "ModView_Core.h"


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
