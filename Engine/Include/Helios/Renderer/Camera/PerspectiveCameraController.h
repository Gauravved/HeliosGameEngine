#pragma once

#include<Helios/Core/TimeStep.h>
#include<Helios/Events/MouseEvent.h>
#include<Helios/Events/ApplicationEvent.h>
#include<Helios/Renderer/Camera/PerspectiveCamera.h>

namespace Helios {
	class PerspectiveCameraController {
	public:
		explicit PerspectiveCameraController(
			float fov,
			float aspectratio,
			float nearClip,
			float farClip
		);

		void OnUpdate(TimeStep timestep);
		void OnEvent(Event& event);

		[[nodiscard]]
		PerspectiveCamera& GetCamera() { return m_Camera; }

		[[nodiscard]]
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnWindowResize(WindowResizeEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);

	private:
		PerspectiveCamera m_Camera;

		float m_MovementSpeed = 5.0f;
		float m_MouseSensitivity = 0.1f;

		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
		bool m_FirstMouse = true;
	};
}