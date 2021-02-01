#pragma once



#include "Application.h"



int main() {

	MV::Application* app = MV::CreateApplication();
	app->Run();
	delete app;

}

