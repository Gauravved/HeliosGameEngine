#include <iostream>

#include <Helios/Core/Application.h>
#include<Helios/Renderer/Renderer.h>
#include<Helios/Core/Log.h>

namespace Helios {

	Application::Application() {

		m_Window = std::unique_ptr<Window>(Window::Create());

		// Setting Event Callback
		m_Window->SetEvenCallback(
			[this](Event& e) {
				OnEvent(e);
			}
		);
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

	// Orchestrating the Event occurance
	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		// Calling dispatcher for WindowCloseEvent. The parameter passed is Lambda callback function for OnWindowClose
		dispatcher.Dispatch<WindowCloseEvent>(
			[this](WindowCloseEvent& e) {
				return OnWindowClose(e);
			}
		);

		// Calling dispatcher for WindowsResizeEvent
		dispatcher.Dispatch<WindowResizeEvent>(
			[this](WindowResizeEvent& e) {
				return OnWindowResize(e);
			}
		);
	}

	// What to do on window close event
	bool Application::OnWindowClose(WindowCloseEvent& event) {
		HL_CORE_INFO("Shutting Down");
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event) {
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		HL_CORE_INFO("New Size: {}",event.ToString());
		return false;
	}

	Application::~Application() = default;
}