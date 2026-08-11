#pragma once

namespace Helios {
	class TimeStep {
	public:
		constexpr TimeStep(float time = 0.0f) :m_Time(time) {}

		constexpr float GetSeconds() const { return m_Time; }
		constexpr float GetMilliSeconds() const { return m_Time * 100.f; }

		constexpr operator float() const {
			return m_Time;
		}

	private:
		float m_Time;
	};
}