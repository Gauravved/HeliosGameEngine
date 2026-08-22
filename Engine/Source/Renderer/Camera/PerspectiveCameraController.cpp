#include<Helios/Renderer/Camera/PerspectiveCameraController.h>
#include<Helios/Input/Input.h>
#include<Helios/Core/Log.h>
#include<Helios/Events/MouseEvent.h>
#include<Helios/Events/ApplicationEvent.h>

namespace Helios {
	PerspectiveCameraController::PerspectiveCameraController(
		float fov,
		float aspectRatio,
		float nearClip,
		float farClip
	) :m_Camera(fov, aspectRatio, nearClip, farClip) {

	}

	void PerspectiveCameraController::OnUpdate(TimeStep timeStep) {
		if (!Input::IsMouseButtonPressed(MouseButton::Right)) {
			return;
		}

		// Get movement
		// Movement is frame-rate independent: Speed × Delta Time.
		float movement = m_MovementSpeed * timeStep.GetSeconds();

		// Get camera position
		glm::vec3 position = m_Camera.GetPosition();

		HL_CORE_INFO("Keyboard Movement detected: {}", movement);

		// Movements
		// Move relative to the camera's current orientation, not world axes.
		if (Input::IsKeyPressed(KeyCode::W)) {
			position += m_Camera.GetForwardDirection() * movement;
		}
		if (Input::IsKeyPressed(KeyCode::S)) {
			position -= m_Camera.GetForwardDirection() * movement;
		}
		if (Input::IsKeyPressed(KeyCode::A)) {
			position -= m_Camera.GetRightDirection() * movement;
		}
		if (Input::IsKeyPressed(KeyCode::D)) {
			position += m_Camera.GetRightDirection() * movement;
		}
		if (Input::IsKeyPressed(KeyCode::E)) {
			position -= m_Camera.GetUpDirection() * movement;
		}
		if (Input::IsKeyPressed(KeyCode::Q)) {
			position += m_Camera.GetUpDirection() * movement;
		}

		m_Camera.SetPosition(position);
	}

	void PerspectiveCameraController::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseMovedEvent>(
			[this](MouseMovedEvent& event) {
				return OnMouseMoved(event);
			}
		);

		dispatcher.Dispatch<WindowResizeEvent>(
			[this](WindowResizeEvent& event) {
				return OnWindowResize(event);
			}
		);

		dispatcher.Dispatch<MouseScrolledEvent>(
			[this](MouseScrolledEvent& event) {
				return OnMouseScrolled(event);
			}
		);

	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& event) {
		if (!Input::IsMouseButtonPressed(MouseButton::Right)) {
			m_FirstMouse = true;
			return false;
		}

		float mouseX = event.GetMouseX();
		float mouseY = event.GetMouseY();

		if (m_FirstMouse) {
			m_LastMouseX = mouseX;
			m_LastMouseY = mouseY;
			m_FirstMouse = false;

			return false;
		}

		float deltaX = mouseX - m_LastMouseX;
		float deltaY = mouseY - m_LastMouseY;

		m_LastMouseX = mouseX;
		m_LastMouseY = mouseY;

		glm::vec3 rotation = m_Camera.GetRotation();

		HL_CORE_INFO("Rotation detected: {} {} {}", rotation.x, rotation.y, rotation.z);

		rotation.y += deltaX * m_MouseSensitivity;
		rotation.x += deltaY * m_MouseSensitivity;

		m_Camera.SetRotation(rotation);

		return false;

	}

	bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& event) {
		float aspectRatio = static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
		m_Camera.SetProjection(m_Camera.GetFOV(), aspectRatio, m_Camera.GetNearClip(), m_Camera.GetFarClip());
		return false;
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
		float fov = m_Camera.GetFOV();
		fov -= event.GetYOffset() * m_ZoomSpeed;
		// To keep the FOV in 20 - 90 degrees
		fov = glm::clamp(fov, 20.0f, 90.0f);

		m_Camera.SetProjection(
			fov, m_Camera.GetAspectRatio(), m_Camera.GetNearClip(), m_Camera.GetFarClip()
		);

		return false;
	}
}