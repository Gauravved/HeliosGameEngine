// #include <iostream>

#include <Helios/Platform/Windows/WindowsWindow.h>
#include<Helios/Renderer/OpenGL/OpenGLContext.h>
#include<Helios/Events/ApplicationEvent.h>


namespace Helios {
	Window* Window::Create(const WindowProperties& properties) {
		return new WindowsWindow(properties);
	}

	void WindowsWindow::SetEvenCallback(const EventCallbackFn& callbackFunc) {
		m_Data.EventCallback = callbackFunc;
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) {
		Init(properties);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	// WindowProc definition
	LRESULT CALLBACK WindowsWindow::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		// Retieving the "this" object from the lparam
		// WM_NCCREATE is the very first message Windows sends when a window is being created.
		// First message sent during window creation; used to associate our C++ object with the HWND.

		if (message == WM_NCCREATE) {

			// Retrieve the window creation data supplied by CreateWindowExW().
			// Convert the raw LPARAM into a pointer to the window creation structure.
			CREATESTRUCTW* createStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);

			// Retrieve the user-defined pointer passed to CreateWindowExW().
			// Recover the WindowsWindow instance passed during window creation.
			WindowsWindow* windowsWindow = static_cast<WindowsWindow*>(createStruct->lpCreateParams);

			// Store the WindowsWindow pointer inside the HWND for future message handling.
			// Index identifying the per-window user-defined storage location.
			// Convert the object pointer into the integer type expected by Win32.
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowsWindow));

			// Let Windows perform its default processing for WM_NCCREATE.
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}

		WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

		switch(message){
		case WM_ERASEBKGND:
			//  Return 1 (non-zero) to tell Windows we handled the background erasure.
			//  This stops the OS from painting a black rectangle over our OpenGL frame.
			return 1;

		case WM_PAINT:
			//  Validate the window so Windows stops spamming the message queue with paint requests
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			//  We do nothing here because OpenGL handles the actual drawing
			EndPaint(hwnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_CLOSE:
			WindowCloseEvent event;

			if (window) {
				window->m_Data.EventCallback(event);
			}

			//DestroyWindow(hwnd);

			return 0;

		}

		return DefWindowProcW(hwnd, message, wParam, lParam);
	}

	void WindowsWindow::Init(const WindowProperties& properties) {
		// initialize the windows
		//  Initialize the windows property
		m_Data = properties;
		// GetModuleHandleW() because of wide strings and newer version
		m_Instance = GetModuleHandleW(nullptr);

		// Initialize window with all values 0
		WNDCLASSEXW windowClass{};
		windowClass.cbSize = sizeof(WNDCLASSEXW);

		windowClass.style = CS_OWNDC;

		// Long Pointer to Function Window Procedure. Every windows event from mouse click, keyboard interruption to paint and close will eventually come here.
		windowClass.lpfnWndProc = WindowProc;

		// Setting instance used earlier
		windowClass.hInstance = m_Instance;

		// lpszClassName is a member structure field used to assign a unique text name to a registered window template. LPSZ = Long Pointer String Zero Terminatied
		windowClass.lpszClassName = L"HeliosWindow";

		// Loading Cursor
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

		// Registering the Class. egisterClass(&windowClass) creates a reusable window template. It takes a pointer to a WNDCLASS structure (defining elements like the window procedure, background brush, and cursor) 
		//  and makes the class available to the system so you can instantiate it using CreateWindow
		RegisterClassExW(&windowClass);

		// Creating the window
		m_Handle = CreateWindowExW(
			0,															// DWORD 0 for no extendent window style
			windowClass.lpszClassName,									// Class Name
			L"Helios Engine",											// Window Title
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,	// Standard desktop window. This automatically gives minimize maximize resize close button
			CW_USEDEFAULT,												// Defines Starting position
			CW_USEDEFAULT,												// Defaines Starting position
			m_Data.m_Width,
			m_Data.m_Height,
			nullptr,													// No parent window
			nullptr,													// No Menus
			m_Instance,													// Current Instance created
			this														// Reference to the current WindowsWindow 
		);
		/*RECT rect{};
		GetClientRect(m_Handle, &rect);

		std::cout
			<< "Client Size = "
			<< rect.right - rect.left
			<< " x "
			<< rect.bottom - rect.top
			<< '\n';

		if (!m_Handle) {
			MessageBoxW(
				nullptr,
				L"Failed to create the window",
				L"Error",
				MB_OK | MB_ICONERROR
			);
			return;
		}*/

		// show window
		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);

		// Creating OpenGL context
		m_GraphicsContext = std::make_unique<OpenGLContext>(m_Handle);
		m_GraphicsContext->Init();
	}

	void WindowsWindow::Shutdown() {
		// shutting the window down
	}

	void WindowsWindow::OnUpdate() {
		MSG message;
		while ((PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))) {
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}

		m_GraphicsContext->SwapBuffer();
	}

	uint32_t WindowsWindow::GetWidth() const {
		return m_Data.m_Width;
	}
	uint32_t WindowsWindow::GetHeight() const {
		return m_Data.m_Height;
	}
	
}