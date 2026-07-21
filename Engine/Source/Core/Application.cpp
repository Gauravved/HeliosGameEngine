#include <iostream>

#include <Helios/Core/Application.h>
#include<Helios/Renderer/Renderer.h>
#include<Helios/Core/Log.h>

namespace Helios {

	Application::Application() {

		HL_CORE_INFO("Helios Logger Initialized");
		HL_CORE_WARN("This is a warning");
		HL_CORE_ERROR("This is an error");

		HL_INFO("Sandbox Logger Initialized");

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