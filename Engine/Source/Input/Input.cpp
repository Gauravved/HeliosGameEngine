#include<utility>

#include<Helios/Input/Input.h>

namespace Helios {
	std::unique_ptr<Input> Input::s_Instance = nullptr;

	void Input::SetInstance(std::unique_ptr<Input> instance) {
		s_Instance = std::move(instance);
	}
}