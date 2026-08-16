#pragma once

#include<sstream>
#include<string>
#include<functional>

// Generates the type information for an Event
#define HL_EVENT_CLASS_TYPE(type)                    \
    static EventType GetStaticType() {               \
        return EventType::type;                      \
    }                                                \
    virtual EventType GetEventType() const override {\
        return GetStaticType();                      \
    }                                                \
    virtual const char* GetName() const override {   \
        return #type;                                \
    }

// Macro for Event Category
#define HL_EVENT_CLASS_CATEGORY(category)				\
		virtual int GetCategoryFlags() const override{	\
			return category;							\
		}													

namespace Helios {
	enum class EventType {
		None = 0,

		// Application Events
		WindowClose,
		WindowResize,

		// Keyboard Events
		KeyPressed,
		KeyReleased,

		// Mouse Events
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		None = 0,

		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4
	};

	class Event {
	public:

		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags()const = 0;

		virtual std::string ToString() const {
			return GetName();
		}

		bool IsInCategory(EventCategory category) const {
			return GetCategoryFlags() & category;
		}


	public:
		bool Handled = false;

	};

	// Event Dispatcher for Event Management
	class EventDispatcher {

	public:
		EventDispatcher(Event& event) : m_Event(event) {
		}

		/* template<typename T> - works with any event type.
		std::function<bool(T&)> - accepts any callable that takes a T& and returns bool.
		const& - avoids copying the std::function object.
		bool Dispatch(...) - returns whether the dispatch actually occurred. */
		template<typename T>
		bool Dispatch(const std::function<bool(T&)>& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}


	private:
		// Storing reference not pointer or copy. If not reference then why storing WindowResize it will cause object slicing to fit Event and the data unique to WindowResize will disappear.
		// Why not pointer? a dispatcher cannot exist without an event. There is no valid state where it has "no event."
		Event& m_Event;
	};
}