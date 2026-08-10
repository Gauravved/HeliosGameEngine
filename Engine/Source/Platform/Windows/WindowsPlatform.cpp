#include<memory>

#include<Helios/Platform/Windows/WindowsPlatform.h>
#include<Helios/Platform/Windows/WindowsInput.h>
#include<Helios/Window/Window.h>

namespace Helios {
	void WindowsPlatform::Initialize(Window& window) {
		Input::SetInstance(std::make_unique<WindowsInput>(window));
	}

	void WindowsPlatform::Shutdown() {

	}
}