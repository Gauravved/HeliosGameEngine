#include<algorithm>

#include<Helios/Core/LayerStack.h>
#include<Helios/Core/Log.h>

namespace Helios {

	LayerStack::LayerStack() = default;

	LayerStack::~LayerStack() {
		// Destroy the Layers in reverse of how they are created
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it) {
			(*it)->OnDetach();
		}
		HL_CORE_INFO("All Layers Detached");
		HL_CORE_INFO("LayerStack Destroyed");
	}

	void LayerStack::PushLayer(const std::shared_ptr<Layer>& layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		++m_LayerInsertIndex;
	}

	void LayerStack::PushOverlay(const std::shared_ptr<Layer>& overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(const std::shared_ptr<Layer>& layer) {
		auto iterator = std::find(
			m_Layers.begin(),
			m_Layers.begin() + m_LayerInsertIndex,
			layer
		);

		if (iterator != m_Layers.begin() + m_LayerInsertIndex) {
			m_Layers.erase(iterator);
			--m_LayerInsertIndex;
		}
	}

	void LayerStack::PopOverlay(const std::shared_ptr<Layer>& overlay) {
		auto iterator = std::find(
			m_Layers.begin() + m_LayerInsertIndex,
			m_Layers.end(),
			overlay
		);

		if (iterator != m_Layers.end()) {
			m_Layers.erase(iterator);
		}
	}
}