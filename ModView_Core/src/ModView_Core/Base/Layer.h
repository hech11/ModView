#pragma once


#include "mvpch.h"
#include "ModView_Core/Event/Event.h"

namespace MV {

	class Layer {
		public :
			Layer(const std::string& name = "Layer") : m_Name(name) { }
			virtual ~Layer() { }

			virtual void OnAttach() {}
			virtual void OnDetach() {}

			virtual void OnEvent(Event& e) {}
			virtual void OnUpdate() {}


			inline std::string& GetName() { return m_Name; }
		protected : 
			std::string m_Name;
	};

	class LayerStack {

		public :
			~LayerStack();
			void OnUpdate();

			void PushLayer(Layer* layer);
			void PopLayer(Layer* layer);
			void PopBackLayer();

			inline std::vector<Layer*>& GetLayerStack() { return m_LayerStack; }

		private :
			std::vector<Layer*> m_LayerStack;
	};

}