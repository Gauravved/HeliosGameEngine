#pragma once

#include<Helios/Input/Input.h>

namespace Helios {
	class WindowsInput : public Input {
	protected:
		bool IsKeyPressedImpl(KeyCode key) const override;
		bool IsMouseButtonPressedImpl(MouseButton button) const override;
		float GetMouseXImpl() const override;
		float GetMouseYImpl() const override;
	};
}