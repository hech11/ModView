#include "ModView_Core.h"


class Sandbox : public ModView::Application {


	public :

		Sandbox() {

		}
		~Sandbox() {}

};



ModView::Application* ModView::CreateApplication() {
	return new Sandbox();
}
