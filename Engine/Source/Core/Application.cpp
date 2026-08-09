#include <iostream>

#include <Helios/Core/Application.h>
#include<Helios/Renderer/Renderer.h>
#include<Helios/Core/Log.h>
#include<Helios/Platform/Windows/WindowsPlatform.h>
#include<Helios/Input/Input.h>

namespace Helios {

	Application::Application() {

		m_Window = std::unique_ptr<Window>(Window::Create());
		WindowsPlatform::Initialize();

		// Setting Event Callback
		m_Window->SetEventCallback(
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
			if (Input::IsKeyPressed(KeyCode::W)) {
				HL_CORE_INFO("W is pressed");
			}
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

		// Calling dispatcher for KeyPressedEvent
		dispatcher.Dispatch<KeyPressedEvent>(
			[this](KeyPressedEvent& e) {
				return OnKeyPressed(e);
			}
		);

		// Calling dispatcher for KeyReleasedEvent
		dispatcher.Dispatch<KeyReleasedEvent>(
			[this](KeyReleasedEvent& e) {
				return OnKeyReleased(e);
			}
		);

		// Calling dispatcher for MouseMovedEvent
		dispatcher.Dispatch<MouseMovedEvent>(
			[this](MouseMovedEvent& e) {
				return OnMouseMoved(e);
			}
		);

		// Calling dispatcher for MouseScrolledEvent
		dispatcher.Dispatch<MouseScrolledEvent>(
			[this](MouseScrolledEvent& e) {
				return OnMouseScrolled(e);
			}
		);

		// Calling dispatcher for MouseButtonPressed and MouseButtonReleased Events
		dispatcher.Dispatch<MouseButtonPressedEvent>(
			[this](MouseButtonPressedEvent& e) {
				return OnMouseButtonPressed(e);
			}
		);

		dispatcher.Dispatch<MouseButtonReleasedEvent>(
			[this](MouseButtonReleasedEvent& e) {
				return OnMouseButtonReleased(e);
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

	bool Application::OnKeyPressed(KeyPressedEvent& event) {
		HL_CORE_INFO("{}", event.ToString());
		return false;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& event) {
		HL_CORE_INFO("{}", event.ToString());
		return false;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& event) {
		HL_CORE_INFO("{}", event.ToString());
		return false;
	}

	bool Application::OnMouseScrolled(MouseScrolledEvent& event) {
		HL_CORE_INFO("{}", event.ToString());
		return false;
	}

	bool Application::OnMouseButtonPressed(MouseButtonPressedEvent& event) {
		HL_CORE_INFO("{}", event.ToString());
		return false;
	}

	bool Application::OnMouseButtonReleased(MouseButtonReleasedEvent& event) {
		HL_CORE_INFO("{}", event.ToString());
		return false;
	}

	Application::~Application() = default;
}