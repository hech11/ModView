#pragma once

#include "Event/Event.h"
#include "Event/WindowEvents.h"
#include "Base/Window.h"


namespace MV {

	class Application {

		public: 

			Application();
			virtual  ~Application();


			void OnEvent(Event& e);
			void Run();

			static Application& GetApp() { return *s_Instance; }


			Scoped<Window>& GetWindow() { return m_Window; }


		private :
			bool m_IsRunning = false;
			static Application* s_Instance;

			Scoped<Window> m_Window;

		private :
			bool OnWindowClose(WindowClosedEvent& e);

	};


	Application* CreateApplication();

}