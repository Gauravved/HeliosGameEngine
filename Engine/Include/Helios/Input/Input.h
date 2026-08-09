#pragma once

#include<memory>

#include<Helios/Input/KeyCodes.h>
#include<Helios/Input/MouseButtonCodes.h>

namespace Helios {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode keyCode) {
			return s_Instance->IsKeyPressedImpl(keyCode);
		}
		static bool IsMouseButtonPressed(MouseButton button) {
			return s_Instance->IsMouseButtonPressedImpl(button);
		}
		static float GetMouseX() {
			return s_Instance->GetMouseXImpl();
		}
		static float GetMouseY() {
			return s_Instance->GetMouseYImpl();
		}

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keyCode) const = 0;
		virtual bool IsMouseButtonPressedImpl(MouseButton button) const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;

	private:
		static std::unique_ptr<Input> s_Instance;

		protected:
			static void SetInstance(std::unique_ptr<Input> instance);

			friend class WindowsPlatform;
	};
}