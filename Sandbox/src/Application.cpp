#include "ModView_Core.h"


class Sandbox : public MV::Application {


	public :

		Sandbox() {

		}
		~Sandbox() {}

};



MV::Application* MV::CreateApplication() {
	return new Sandbox();
}
