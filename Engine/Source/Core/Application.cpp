#include <iostream>

#include <Helios/Core/Application.h>
#include<Helios/Renderer/Renderer.h>
#include<Helios/Core/Log.h>

namespace Helios {

	Application::Application() {

		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	void Application::Run() {
		HL_CORE_INFO("Window created in {} x {} resolution",m_Window->GetWidth(), m_Window->GetHeight());
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