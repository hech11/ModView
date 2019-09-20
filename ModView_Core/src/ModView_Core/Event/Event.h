#pragma once



#include "ModView_Core/Base/Base.h"
#include "mvpch.h"



namespace MV {


	enum class EventType {

		None  = 0,
		KeyPressed, KeyReleased,
		MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled,
		WindowClose, WindowResize, WindowLostFocus, WindowGainedFocus, WindowMove

	};



	#define EVENT_CLASS_TYPE(x) static EventType GetStaticEventType() {return EventType::##x;}\
								virtual EventType GetEventType() const override{return GetStaticEventType();}\
								virtual const char* GetName() const override{ return #x;}\


	class Event {

		public :
			bool Handled = false;

			virtual EventType GetEventType() const = 0;
			//Debugging
			virtual const char* GetName() const = 0;
			virtual std::string ToString() const { return GetName(); }

	};



	class EventDispatcher {

		public :
			EventDispatcher(Event& e) : m_Event(e) {}

			template<typename T>
			bool Dispatch(std::function<bool(T&)> func) {
				if (m_Event.GetEventType() == T::GetStaticEventType()) {
					m_Event.Handled = func(*(T*)& m_Event);
					return true;
				}
				return false;
			}

		private :
			Event& m_Event;
	};
}