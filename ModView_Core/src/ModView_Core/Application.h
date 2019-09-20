#pragma once

#include "Event/Event.h"


namespace MV {

	class Application {

		public: 

			Application();
			virtual  ~Application();


			void OnEvent(Event& e);
			void Run();

			static Application& GetApp() { return *s_Instance; }

		private :
			static Application* s_Instance;
	};


	Application* CreateApplication();

}