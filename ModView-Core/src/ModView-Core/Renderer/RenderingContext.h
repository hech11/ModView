#pragma once


struct GLFWwindow;
namespace MV {

	class RenderingContext {
		public :
			RenderingContext(GLFWwindow* WindowHandle) : m_WindowHandle(WindowHandle) {}
			void Init();
			void SwapBuffers();

		private :
			GLFWwindow* m_WindowHandle;
	};

}