#include<Windows.h>

#include<Helios/Platform/Windows/WindowsInput.h>
#include<Helios/Platform/Windows/WindowsKeyMap.h>
#include<Helios/Window/Window.h>

namespace Helios {
	WindowsInput::WindowsInput(Window& window) : m_Window(window) {}

	bool WindowsInput::IsKeyPressedImpl(KeyCode key) const {
		const uint32 virtualKey = WindowsKeyMap::ToVirtualKey(key);

		if (virtualKey == 0) {
			return false;
		}
		constexpr SHORT KeyPressedMask = 0x8000;

		// GetAsyncKeyState() returns a 16-bit value where the highest bit indicates
		// whether the key is currently pressed.
		return (GetAsyncKeyState(virtualKey) & KeyPressedMask) != 0;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(MouseButton button) const {
		int virtualButton = 0;

		switch (button) {
		case MouseButton::Left: virtualButton = VK_LBUTTON; break;
		case MouseButton::Right: virtualButton = VK_RBUTTON; break;
		case MouseButton::Middle: virtualButton = VK_MBUTTON; break;
		case MouseButton::Button4: virtualButton = VK_XBUTTON1; break;
		case MouseButton::Button5: virtualButton = VK_XBUTTON2; break;
		}

		// Hexadecimal:0x8000 Binary : 1000 0000 0000 0000 Only bit 15 is set.
		// Bit 15 (highest bit)->Is the key currently DOWN ?
		// Bit 0  (lowest bit)->Was the key pressed since the last call ? (legacy behavior)

		constexpr SHORT ButtonPressedMasked = 0x8000;

		// GetAsyncKeyState() also works for mouse buttons.
		// The highest bit is set while the button is currently pressed.
		return (GetAsyncKeyState(virtualButton) & ButtonPressedMasked) != 0;
	}
	float WindowsInput::GetMouseXImpl() const {
		POINT point{};
		HWND hwnd = static_cast<HWND>(m_Window.GetNativeWindow());
		// Retrieve the current cursor position in screen coordinates.
		GetCursorPos(&point);
		ScreenToClient(hwnd, &point);

		return static_cast<float>(point.x);
	}
	float WindowsInput::GetMouseYImpl() const {
		POINT point{};
		HWND hwnd = static_cast<HWND>(m_Window.GetNativeWindow());
		GetCursorPos(&point);
		ScreenToClient(hwnd, &point);
		return static_cast<float>(point.y);
	}
}