#pragma once

#include<Helios/Core/Base.h>
#include<Helios/Events/Event.h>

namespace Helios {
	class MouseMovedEvent: public Event {
	public:
		MouseMovedEvent(float mouseX, float mouseY): m_MouseX(mouseX), m_MouseY(mouseY){}

		// Getters
		float GetMouseX() const { return m_MouseX; }
		float GetMouseY() const { return m_MouseY; }

		// Macros
		HL_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		HL_EVENT_CLASS_TYPE(MouseMoved)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrolledEvent :public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset): m_XOffset(xOffset), m_YOffset(yOffset){}

		// Getters
		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		// Macros
		HL_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		HL_EVENT_CLASS_TYPE(MouseScrolled)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

	private:
		float m_XOffset;
		float m_YOffset;
	};

	class MouseButtonEvent :public Event {
	protected:
		MouseButtonEvent(uint16 button) :m_Button(button) {}

	public:
		// Getter 
		uint16 GetMouseButton() const { return m_Button; }

		// Macro for Category only
		HL_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		uint16 m_Button;
	};

	class MouseButtonPressedEvent :public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(uint16 button) : MouseButtonEvent(button) {}

		// Marco for class type
		HL_EVENT_CLASS_TYPE(MouseButtonPressed)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Button Pressed: " << m_Button;
			return ss.str();
		}

	};

	class MouseButtonReleasedEvent :public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(uint16 button) :MouseButtonEvent(button) {}

		// Macro for class type
		HL_EVENT_CLASS_TYPE(MouseButtonReleased)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Button Released" << m_Button;
			return ss.str();
		}
	};
}