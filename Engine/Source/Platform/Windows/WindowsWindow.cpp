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

	//WindowProc definition
	LRESULT CALLBACK WindowsWindow::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch(message){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		}

		return DefWindowProcW(hwnd, message, wParam, lParam);
	}

	void WindowsWindow::Init(const WindowProperties& properties) {
		//initialize the windows
		// Initialize the windows property
		m_Data = properties;
		//GetModuleHandleW() because of wide strings and newer version
		m_Instance = GetModuleHandleW(nullptr);

		//Initialize window with all values 0
		WNDCLASSEXW windowClass{};
		windowClass.cbSize = sizeof(WNDCLASSEXW);

		windowClass.style = CS_HREDRAW | CS_VREDRAW;

		//Long Pointer to Function Window Procedure. Every windows event from mouse click, keyboard interruption to paint and close will eventually come here.
		windowClass.lpfnWndProc = WindowProc;

		//Setting instance used earlier
		windowClass.hInstance = m_Instance;

		//lpszClassName is a member structure field used to assign a unique text name to a registered window template. LPSZ = Long Pointer String Zero Terminatied
		windowClass.lpszClassName = L"HeliosWindow";

		//Loading Cursor
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

		//Registering the Class. egisterClass(&windowClass) creates a reusable window template. It takes a pointer to a WNDCLASS structure (defining elements like the window procedure, background brush, and cursor) 
		// and makes the class available to the system so you can instantiate it using CreateWindow
		RegisterClassExW(&windowClass);

		//Creating the window
		m_Handle = CreateWindowExW(
			0, //DWORD 0 for no extendent window style
			windowClass.lpszClassName, //Class Name
			L"Helios Engine", //Window Title
			WS_OVERLAPPEDWINDOW, //Standard desktop window. This automatically gives minimize maximize resize close button
			CW_USEDEFAULT, //Defines Starting position
			CW_USEDEFAULT, //Defaines Starting position
			m_Data.m_Width,
			m_Data.m_Height,
			nullptr, //No parent window
			nullptr, //No Menus
			m_Instance, //Current Instance created
			nullptr //No additional Data
		);

		if (!m_Handle) {
			MessageBoxW(
				nullptr,
				L"Failed to create the window",
				L"Error",
				MB_OK | MB_ICONERROR
			);
			return;
		}

		//show window
		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);

	}

	void WindowsWindow::Shutdown() {
		//shutting the window down
	}

	void WindowsWindow::OnUpdate() {
		MSG message;
		while ((PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))) {
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}

	uint32_t WindowsWindow::GetWidth() const {
		return m_Data.m_Width;
	}
	uint32_t WindowsWindow::GetHeight() const {
		return m_Data.m_Height;
	}
	
}