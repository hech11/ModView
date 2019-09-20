#pragma once

#include "Event.h"


namespace MV {


	

	// ********* Key events ********* //




	class KeyEventBase : public Event {

		public :
			KeyEventBase(int keycode) : m_KeyCode(keycode) {}

			inline int GetKeyCode() const { return m_KeyCode; }
		protected:
			int m_KeyCode;
	};
	class KeyPressedEvent : public KeyEventBase {

		public :
			KeyPressedEvent(int keycode, int repeatCount) : KeyEventBase(keycode), m_RepeatCount(repeatCount){}

			inline int GetRepeatCount() const { return m_RepeatCount; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "[KeyPressed Event] KeyCode : " << m_KeyCode << ", Repeat count: " << m_RepeatCount;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyPressed);

		private :
			int m_RepeatCount;


	};

	class KeyReleasedEvent : public KeyEventBase {

		public :
			KeyReleasedEvent(int keycode) : KeyEventBase(keycode) {}

			std::string ToString() const override {
				std::stringstream ss;
				ss << "[KeyReleased Event] KeyCode : " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyReleased);


		private :

	};







	// ********* Mouse events ********* //





	class MouseEventBase : public Event {

		public :
			MouseEventBase(int button) : m_Button(button) {}

			inline int GetMouseButton() const { return m_Button; }

		protected: 
			int m_Button;
	};


	class MouseButtonPressedEvent : public MouseEventBase {

		public :
			MouseButtonPressedEvent(int button, int repeatCount) : MouseEventBase(button), m_RepeatCount(repeatCount) {}

			inline int GetRepeatCount() const { return m_RepeatCount; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "[MouseButtonPressedEvent Event] Button : " << m_Button << ", Repeat count: " << m_RepeatCount;
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonPressed);



		private :
			int m_RepeatCount;

	};


	
	class MouseButtonReleasedEvent : public MouseEventBase {

		public :
			MouseButtonReleasedEvent(int button) : MouseEventBase(button) {}

			std::string ToString() const override {
				std::stringstream ss;
				ss << "[MouseButtonPressedEvent Event] Button : " << m_Button;
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonReleased);


	};


	class MouseMovedEvent : public Event{

		MouseMovedEvent(float xpos, float ypos) : m_MouseX(xpos), m_MouseY(ypos) {}

		inline float GetXPos() const { return m_MouseX; }
		inline float GetYPos() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "[MouseMovedEvent Event] : xPos(" << m_MouseX << "), yPos(" << m_MouseY << ")";
			return ss.str();
		}


		EVENT_CLASS_TYPE(MouseMoved);


		private :
			float m_MouseX, m_MouseY;
	};



	
	class MouseScrolledEvent : public Event{

		MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "[MouseScrolledEvent Event] : xOffset(" << m_xOffset << "), yOffset(" << m_yOffset << ")";
			return ss.str();
		}


		EVENT_CLASS_TYPE(MouseScrolled);


		private :
			float m_xOffset, m_yOffset;
	};

}