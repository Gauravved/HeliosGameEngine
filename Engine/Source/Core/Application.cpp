#include <Helios/Core/Application.h>

#include <iostream>

namespace Helios {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
	Application::~Application() = default;
}