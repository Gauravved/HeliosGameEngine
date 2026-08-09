#include<memory>

#include<Helios/Platform/Windows/WindowsPlatform.h>
#include<Helios/Platform/Windows/WindowsInput.h>

namespace Helios {
	void WindowsPlatform::Initialize() {
		Input::SetInstance(std::make_unique<WindowsInput>());
	}

	void WindowsPlatform::Shutdown() {

	}
}