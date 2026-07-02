#pragma once

#include <Helios/Window/Window.h>
#include<Windows.h>
namespace Helios {
	class WindowsWindow : public Window {
	public:
		//Constructor to initialize the wndows window with window properties
		WindowsWindow(const WindowProperties& properties);

		virtual ~WindowsWindow();

		//Override the parent class functions for windows compatibility
		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;

	private:
		//Windows Fucntions for initializing window
		void Init(const WindowProperties& properties);
		void Shutdown();

	private:
		//HWND = Handle to a Window. It is a pointer to a particular window basically an identifier for the Window so the application can communicate to this window.
		HWND m_WindowsHandle = nullptr;

		//Handle to an Instance. The identifier instance to the current running copy of the window
		HINSTANCE m_WindowInstance = nullptr;

		//Window Properties data
		WindowProperties m_Data;

	};
}