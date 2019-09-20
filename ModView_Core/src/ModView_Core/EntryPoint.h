#pragma once



#include "Application.h"



int main() {

	ModView::Application* app = ModView::CreateApplication();
	app->Run();
	delete app;

}

