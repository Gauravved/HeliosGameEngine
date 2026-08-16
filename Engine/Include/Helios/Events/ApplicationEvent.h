#pragma once

#include<Helios/Core/Base.h>
#include<Helios/Events/Event.h>

namespace Helios {

	// Window Resize Event
	class WindowResizeEvent :public Event {
	public:
		WindowResizeEvent(uint32 width, uint32 height) : m_Width(width), m_Height(height) {
		}

		uint32 GetWidth() const {
			return m_Width;
		}

		uint32 GetHeight() {
			return m_Height;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << m_Width << " x " << m_Height;
			return ss.str();
		}

		HL_EVENT_CLASS_TYPE(WindowResize)
		HL_EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		uint32 m_Width;
		uint32 m_Height;
	};


	// Window Close Event
	class WindowCloseEvent :public Event {
	public:
		HL_EVENT_CLASS_TYPE(WindowClose)
		HL_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}