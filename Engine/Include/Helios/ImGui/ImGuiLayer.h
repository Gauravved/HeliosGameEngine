#pragma once

#include<Helios/Core/Layer.h>
#include<Helios/Renderer/FrameBuffer/FrameBuffer.h>

namespace Helios {
	class ImGuiLayer :public Layer {
	public:
		explicit ImGuiLayer(void* nativeWindow, const std::shared_ptr<FrameBuffer>& frameBuffer);
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(TimeStep timestep) override;
		void OnEvent(Event& event) override;

	private:
		void* m_NativeWindow = nullptr;
		std::shared_ptr<FrameBuffer> m_FrameBuffer;
	};
}