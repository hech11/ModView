#include "mvpch.h"
#include "Layer.h"



namespace MV {


	LayerStack::~LayerStack() {
		for (auto& layer : m_LayerStack) {
			layer->OnDetach();
			delete layer;
		}

		m_LayerStack.clear();
	}

	void LayerStack::OnUpdate(Timestep dt) {
		for (auto& layer : m_LayerStack) {
			layer->OnUpdate(dt);
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_LayerStack.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
			layer->OnDetach();
			delete layer;
		}

	}

	void LayerStack::PopBackLayer() {
		m_LayerStack.back()->OnDetach();
		delete m_LayerStack.back();
		m_LayerStack.pop_back();
	}

}