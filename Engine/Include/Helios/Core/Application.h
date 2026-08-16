#pragma once
#include<memory>

#include<Helios/Window/Window.h>
#include<Helios/Core/LayerStack.h>
#include<Helios/Core/TimeStep.h>
#include<Helios/Events/ApplicationEvent.h>
#include<Helios/Events/KeyEvent.h>
#include<Helios/Events/MouseEvent.h>

// defining application namespace 
namespace Helios{
	class Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		void OnEvent(Event& event);

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);

	protected:
		Window& GetWindow() const { return *m_Window; }

	private:
		bool m_Running = true;
		std::unique_ptr<Helios::Window> m_Window;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	};
}