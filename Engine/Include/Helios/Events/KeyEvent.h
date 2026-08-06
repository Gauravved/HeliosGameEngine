#pragma once

#include<Helios/Core/Base.h>
#include<Helios/Events/Event.h>

namespace Helios {
	// Base class for KeyEvents 
	class KeyEvent :public Event {
	public:

		uint16 GetKey() const { return m_KeyCode; }

		// As this will be keyboard event as well as input event: 
		// Category Input: 0010, Category Keyboard: 0100. OR operation 0110.  0110 AND 0010 = Category Input. But if Category Application then 0110 AND 0001 = 0000 Hence category not present
		HL_EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	protected:
		uint16 m_KeyCode;

	protected:
		KeyEvent(uint16 key) :m_KeyCode(key) {}

	};

	// KeyPressed Event
	class KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(uint16 key):KeyEvent(key){}

		// Event Class Type
		HL_EVENT_CLASS_TYPE(KeyPressed)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Pressed: " << m_KeyCode;
			return ss.str();
		}
	};

	// KeyReleased Event
	class KeyReleasedEvent :public KeyEvent {
	public:
		KeyReleasedEvent(uint16 key) :KeyEvent(key) {}

		// Event Class Type
		HL_EVENT_CLASS_TYPE(KeyReleased)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Released: " << m_KeyCode;
			return ss.str();
		}
	};
}