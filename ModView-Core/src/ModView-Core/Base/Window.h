#pragma once


#include "mvpch.h"
#include "ModView-Core/Event/Event.h"
#include "ModView-Core/Renderer/RenderingContext.h"


struct GLFWwindow;
namespace MV {
	struct WinProps {
		unsigned int Width, Height, xPos, yPos;
		std::string Title;

		WinProps(unsigned int width = 1280, unsigned int height = 720,
			unsigned int xpos = 50, unsigned int ypos = 50, const std::string & title = "ModView")
			: Width(width), Height(height), xPos(xpos), yPos(ypos), Title(title) {

		}
	};

	class Window {

		public :
			Window(const WinProps& props) { StartUp(props); }

			~Window() { ShutDown(); }

			void StartUp(const WinProps& props);
			void ShutDown();

			void OnUpdate();


			void SetTitle(std::string& title);
			void SetVSync(bool enable);

			void SetEventCallback(const std::function<void(Event&)>& callback) { m_WinData.EventCallback = callback; }

			inline std::string& GetTitle() const { m_WinData.props.Title; }
			inline bool IsVSyncEnabled() const { return m_WinData.vSync; }

			inline unsigned int GetXPos() const { return m_WinData.props.xPos; }
			inline unsigned int GetYPos() const { return m_WinData.props.yPos; }

			inline unsigned int GetWidth() const { return m_WinData.props.Width; }
			inline unsigned int GetHeight() const { return m_WinData.props.Height; }

			inline std::pair<unsigned int, unsigned int> GetPos() const { return std::make_pair(GetXPos(), GetYPos()); }
			inline std::pair<unsigned int, unsigned int> GetDimensions() const { return std::make_pair(GetWidth(), GetHeight()); }

			inline GLFWwindow* GetNativeWindow() const { return m_Window; }

		private :
			struct WinData {


				WinProps props;
				bool vSync = false;

				std::function<void(Event&)> EventCallback;
			};
			GLFWwindow* m_Window;
			RenderingContext* m_Context;
			WinData m_WinData;
	};
}