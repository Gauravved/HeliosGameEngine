#pragma once

#include<Helios/Input/Input.h>

namespace Helios {
	class Window;
	class WindowsInput : public Input {
	public:
		explicit WindowsInput(Window& window);
	protected:
		bool IsKeyPressedImpl(KeyCode key) const override;
		bool IsMouseButtonPressedImpl(MouseButton button) const override;
		float GetMouseXImpl() const override;
		float GetMouseYImpl() const override;

	private:
		Window& m_Window;
	};
}