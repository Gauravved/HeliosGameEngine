#include <iostream>
#include<chrono> // To Get Current Time

#include <Helios/Core/Application.h>
#include<Helios/Renderer/Renderer.h>
#include<Helios/Core/Log.h>
#include<Helios/Platform/Windows/WindowsPlatform.h>
#include<Helios/Input/Input.h>

namespace {

	// Setting Clock to capture fram times
	// steady_clock is monotonic and never goes back in time
	using Clock = std::chrono::steady_clock;


}

namespace Helios {

	Application::Application() {

		m_Window = std::unique_ptr<Window>(Window::Create());
		WindowsPlatform::Initialize(*m_Window);

		// Setting the Last Frame to avoid huge delta
		m_LastFrameTime = std::chrono::duration<float>(Clock::now().time_since_epoch()).count();

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

		// Initializing ImGuiLayer 
		m_ImGuiLayer = std::make_shared<ImGuiLayer>(m_Window->GetNativeWindow());

		// Add ImGuiLayer as overlay
		// Overlays are reserved for systems like ImGui, debugging, and profiling that should always sit above normal gameplay/scene layers and receive events first.
		PushOverlay(m_ImGuiLayer);

		while (m_Running) {
			auto now = Clock::now();

			float currentTime = std::chrono::duration<float>(
				now.time_since_epoch()
			).count();

			TimeStep timeStep = currentTime - m_LastFrameTime;

			m_LastFrameTime = currentTime;

			/*if (Input::IsKeyPressed(KeyCode::W)) {
				HL_CORE_INFO("W is pressed");
			}
			if (Input::IsMouseButtonPressed(MouseButton::Left)) {
				HL_CORE_INFO("Left is pressed");
			}*/
			//HL_CORE_INFO("X and Y offsets {}, {}", Input::GetMouseX(), Input::GetMouseY());
			Renderer::BeginFrame();
			for (auto& layer : m_LayerStack) {
				layer->OnUpdate(timeStep);
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

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (event.Handled) {
				break;
			}
			(*it)->OnEvent(event);
		}

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
		//HL_CORE_INFO("{}", event.ToString());
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