#pragma once
#include<string>

// Macro to get EventCategory
#define EVENT_CLASS_TYPE(type)								\
		static EventType GetStaticType(){					\
			return EventType::type							\
		}													\
		virtual EventType GetEventType() const override{	\
			return GetStaticType();							\
		}													\		
		virtual const char* GetName() const override{		\
			return #type;									\
		}													\


#define EVENT_CLASS_CATEGORY(category)						\
		virtual int GetCategoryFlags() const override{		\
			return category;								\
		}													\

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

		EventCategoryApplication		= 1 << 0,
		EventCategoryInput				= 1 << 1,
		EventCategoryKeyboard			= 1 << 2,
		EventCategoryMouse				= 1 << 3,
		EventCategoryMMouseButton		= 1 << 4
	};

	class Event {
	public:

		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags()const = 0;

		virtual std::string ToString() const {
			GetName();
		}

		bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}


	public:
		bool Handled = false;
		
	protected:
	
	private:

	};
}