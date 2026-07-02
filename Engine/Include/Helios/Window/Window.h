#pragma once

#include <string>
#include <cstdint>

namespace Helios {
	struct WindowProperties {
		std::string m_Title = "Helios Game Engine";
		uint32_t m_Width = 1280;
		uint32_t m_Height = 720;
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}