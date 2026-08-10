#pragma once

namespace Helios {
	class Window;
	class WindowsPlatform {
	public:
		static void Initialize(Window& window);
		static void Shutdown();
	};
}