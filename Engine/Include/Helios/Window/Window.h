#pragma once

#include <string>
#include<functional>

#include<Helios/Core/Base.h>
#include<Helios/Events/Event.h>

namespace Helios {
	// It says : "I will call any function that takes an Event& and returns nothing."
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowProperties {
		std::string m_Title = "Helios Game Engine";

		uint32 m_Width = 1280;
		uint32 m_Height = 720;

		EventCallbackFn EventCallback;
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callbackFunc) = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}