#pragma once

#include<memory>
#include<vector>

#include<Helios/Core/Layer.h>
#include<Helios/Core/Base.h>


namespace Helios {

	using Iterator = std::vector<std::shared_ptr<Layer>>::iterator;
	using ConstIterator = std::vector<std::shared_ptr<Layer>>::const_iterator;

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		void PopLayer(const std::shared_ptr<Layer>& layer);
		void PopOverlay(const std::shared_ptr<Layer>& overlay);

		// iterators
		Iterator begin() {
			return m_Layers.begin();
		}
		Iterator end() {
			return m_Layers.end();
		}

		// const iterators:
		ConstIterator begin() const {
			return m_Layers.begin();
		}
		ConstIterator end() const {
			return m_Layers.end();
		}


	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		uint32 m_LayerInsertIndex = 0;
	};
}