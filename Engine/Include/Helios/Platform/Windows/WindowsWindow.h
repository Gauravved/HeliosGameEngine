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

		/*
		* FOR FUTURE REFERENCE
		static: The keyword static is used here because this function is typically wrapped inside a C++ class. Windows requires a standard C-style function pointer for callbacks, 
		but class member functions require an implicit this pointer. Declaring it static removes the hidden this parameter so Windows can successfully call it.
		
		LRESULT: A data type representing the integer value returned to Windows. It holds your program's specific response or confirmation to the operating system.
		CALLBACK: Specifies the calling convention (how parameters are pushed onto the memory stack). Windows uses this to know exactly how to execute the function.
		WindowProc: The actual name of the function. You can technically rename it to anything you want (like WndProc), provided you register the function pointer with Windows.

		*/

		static LRESULT CALLBACK WindowProc(
			HWND hwnd, //A handle to the specific window that received the event
			UINT message, //The event identifier, such as WM_PAINT (the window needs to be drawn) or WM_DESTROY
			WPARAM wParam,
			LPARAM lParam  //Two parameters that carry additional, context-specific data about the event (e.g., coordinates for a mouse click or the specific key pressed on a keyboard)
		);

	private:
		//HWND = Handle to a Window. It is a pointer to a particular window basically an identifier for the Window so the application can communicate to this window.
		HWND m_Handle = nullptr;

		//Handle to an Instance. The identifier instance to the current running copy of the window
		HINSTANCE m_Instance = nullptr;

		//Window Properties data
		WindowProperties m_Data;

	};
}