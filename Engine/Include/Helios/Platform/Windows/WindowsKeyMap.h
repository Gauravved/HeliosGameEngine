#pragma once

#include<Helios/Input/KeyCodes.h>
//#include<Helios/Input/MouseButtonCodes.h>

namespace Helios {
	class WindowsKeyMap {
	public:
		static KeyCode ToKeyCode(uint32 virtualKey);
		//static MouseButton ToMouseButton(uint32 button);
	};
}