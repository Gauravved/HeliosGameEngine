#include <iostream>

#include <Helios/Core/Application.h>
#include<Helios/Renderer/Renderer.h>

namespace Helios {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	void Application::Run() {
		std::cout << m_Window->GetWidth() << " "
			<< m_Window->GetHeight() << std::endl;
		Renderer::Init(
			m_Window->GetWidth(),
			m_Window->GetHeight()
		);
		while (m_Running) {
			Renderer::BeginFrame();
			m_Window->OnUpdate();
			//Renderer::EndFrame();
		}
	}
	Application::~Application() = default;
}