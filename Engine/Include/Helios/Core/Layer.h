#pragma once

#include<string>

#include<Helios/Core/TimeStep.h>

namespace Helios {
	class Layer {
	public:
		explicit Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		// Not Pure virtua because some classes may need all functions and some might not
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(TimeStep timeStep) {};

		const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName;
	};
}