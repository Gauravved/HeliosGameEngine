#pragma once

#include<string>

#include<Helios/Core/TimeStep.h>

namespace Helios {
	class Event;
	class Layer {
	public:
		explicit Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		// Not Pure virtual because some classes may need all functions and some might not
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(TimeStep timeStep) {};
		virtual void OnEvent(Event& event) {};

		const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName;
	};
}