#pragma once

#include<Helios/Core/Layer.h>

namespace Helios {
	class ImGuiLayer :public Layer {
	public:
		explicit ImGuiLayer(void* nativeWindow);
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(TimeStep timestep) override;
		void OnEvent(Event& event) override;

	private:
		void* m_NativeWindow = nullptr;
	};
}