#include <Helios/Platform/Windows/WindowsWindow.h>
#include <iostream>

namespace Helios {
	Window* Window::Create(const WindowProperties& properties) {
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) {
		Init(properties);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& properties) {
		//initialize the windows
		std::cout << "Reached initialization";
	}

	void WindowsWindow::Shutdown() {
		//shutting the window down
	}

	void WindowsWindow::OnUpdate() {
		std::cout << "In loop on update";
	}

	uint32_t WindowsWindow::GetWidth() const {
		return m_Data.m_Width;
	}
	uint32_t WindowsWindow::GetHeight() const {
		return m_Data.m_Height;
	}
	
}