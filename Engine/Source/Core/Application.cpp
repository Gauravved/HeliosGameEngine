#include <iostream>

#include <Helios/Core/Application.h>
#include<Helios/Renderer/Renderer.h>
#include<Helios/Core/Log.h>

namespace Helios {

	Application::Application() {

		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	void Application::PushLayer(const std::shared_ptr<Layer>& layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(const std::shared_ptr<Layer>& overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run() {
		HL_CORE_INFO("Window created in {} x {} resolution",m_Window->GetWidth(), m_Window->GetHeight());
		Renderer::Init(
			m_Window->GetWidth(),
			m_Window->GetHeight()
		);
		while (m_Running) {
			Renderer::BeginFrame();
			for (auto& layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_Window->OnUpdate();
			//Renderer::EndFrame();
		}
	}
	Application::~Application() = default;
}