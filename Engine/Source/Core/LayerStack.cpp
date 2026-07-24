#include<algorithm>

#include<Helios/Core/LayerStack.h>

namespace Helios {

	LayerStack::LayerStack() = default;

	LayerStack::~LayerStack() = default;

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