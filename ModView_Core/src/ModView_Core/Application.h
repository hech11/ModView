#pragma once




namespace ModView {

	class Application {

		public: 

			Application();
			virtual  ~Application();


			void Run();

		private :

	};


	Application* CreateApplication();

}