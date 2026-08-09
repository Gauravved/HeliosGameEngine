#include<Windows.h>

#include<Helios/Platform/Windows/WindowsInput.h>
#include<Helios/Platform/Windows/WindowsKeyMap.h>

namespace Helios {
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
		return false;
	}
	float WindowsInput::GetMouseXImpl() const {
		return 0;
	}
	float WindowsInput::GetMouseYImpl() const {
		return 0;
	}
}