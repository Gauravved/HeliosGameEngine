#pragma once

#include<Helios/Input/KeyCodes.h>
//#include<Helios/Input/MouseButtonCodes.h>

namespace Helios {
	class WindowsKeyMap {
	public:
		static KeyCode TranslateKey(uint32 virtualKey, uint64 lParam);
		//static MouseButton ToMouseButton(uint32 button);
		static uint32 ToVirtualKey(KeyCode keyCode);
	};
}