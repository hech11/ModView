#pragma once

#include "Event.h"


namespace MV {
	

	class WindowClosedEvent : public Event {


		public :
			WindowClosedEvent(){}

			EVENT_CLASS_TYPE(WindowClose);
	};

	class WindowResizeEvent : public Event {


		public:
			WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

			EVENT_CLASS_TYPE(WindowResize);

			inline unsigned int GetWidth() const { return m_Width; }
			inline unsigned int GetHeight() const { return m_Height; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "[WindowResizeEvent Event] : Width(" << m_Width << "), Height(" << m_Height << ")";
				return ss.str();
			}


		private :
			unsigned int m_Width, m_Height;
	};


	class WindowLostFocusEvent : public Event {


		public:
			WindowLostFocusEvent() {}

			EVENT_CLASS_TYPE(WindowLostFocus);

	};

	class WindowGainedFocusEvent : public Event {


		public:
			WindowGainedFocusEvent() {}

			EVENT_CLASS_TYPE(WindowGainedFocus);

	};


	class WindowMovedEvent : public Event {
		public :
			WindowMovedEvent(int xpos, int ypos) : m_xPos(xpos), m_yPos(ypos) {}


			inline int GetXPos() const { return m_xPos; }
			inline int GetYPos() const { return m_yPos; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "[WindowMovedEvent Event] : xPos(" << m_xPos << "), yPos(" << m_yPos << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(WindowMove);

		private :
			int m_xPos, m_yPos;
	};


}