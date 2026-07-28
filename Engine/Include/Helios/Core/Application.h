#pragma once
#include<memory>

#include<Helios/Window/Window.h>
#include<Helios/Core/LayerStack.h>
#include<Helios/Events/Event.h>

// defining application namespace 
namespace Helios{
	class Application {
	private:
		bool m_Running = true;
		std::unique_ptr<Helios::Window> m_Window;
		LayerStack m_LayerStack;

	public:
		Application();
		virtual ~Application();
		void Run();

		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		void OnEvent(Event& event);

	};
}