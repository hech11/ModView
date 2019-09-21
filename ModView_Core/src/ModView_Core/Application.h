#pragma once

#include "Event/Event.h"
#include "Event/WindowEvents.h"
#include "Base/Window.h"
#include "Base/Layer.h"


namespace MV {

	class Application {

		public: 

			Application();
			virtual  ~Application();

			void PushLayer(Layer* layer);
			void PopLayer(Layer* layer);
			void PopBackLayer();


			void OnEvent(Event& e);
			void Run();

			static Application& GetApp() { return *s_Instance; }
			Scoped<Window>& GetWindow() { return m_Window; }


		private :
			bool m_IsRunning = false;
			static Application* s_Instance;
			LayerStack m_LayerStack;
			Scoped<Window> m_Window;

		private :
			bool OnWindowClose(WindowClosedEvent& e);

	};


	Application* CreateApplication();

}