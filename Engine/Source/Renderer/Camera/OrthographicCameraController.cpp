#include<algorithm>

#include<Helios/Input/Input.h>
#include<Helios/Core/Log.h>
#include<Helios/Renderer/Camera/OrthographicCameraController.h>

namespace Helios {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio),
		  m_Camera(-aspectRatio, aspectRatio, -m_ZoomLevel, m_ZoomLevel)
	{ }


	void OrthographicCameraController::OnUpdate(TimeStep timeStep) {
		if (!Input::IsMouseButtonPressed(MouseButton::Right)) {
			return;
		}

		float movement = m_CameraTranslationSpeed * timeStep.GetSeconds();

		HL_CORE_INFO("The movement Captured: {}", movement);

		glm::vec3 position = m_Camera.GetPosition();

		if (Input::IsKeyPressed(KeyCode::A)) {
			position.x -= movement;
		}
		if (Input::IsKeyPressed(KeyCode::D)) {
			position.x += movement;
		}
		if (Input::IsKeyPressed(KeyCode::W)) {
			position.y += movement;
		}
		if (Input::IsKeyPressed(KeyCode::S)) {
			position.y -= movement;
		}

		m_Camera.SetPosition(position);
	}

	void OrthographicCameraController::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseScrolledEvent>(
			[this](MouseScrolledEvent& event) {
				return OnMouseScrolledEvent(event);
			}
		);

		dispatcher.Dispatch<WindowResizeEvent>(
			[this](WindowResizeEvent& event) {
				return OnWindowResizedEvent(event);
			}
		);
		dispatcher.Dispatch<MouseMovedEvent>(
			[this](MouseMovedEvent& event) {
				return OnMouseMovedEvent(event);
			}
		);

	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& event) {
		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		HL_CORE_INFO("Zoom Level Changed: {}", m_ZoomLevel);

		m_Camera.SetProjection(
			-m_AspectRatio * m_ZoomLevel,
			m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel,
			m_ZoomLevel
		);

		return false;
	}

	bool OrthographicCameraController::OnWindowResizedEvent(WindowResizeEvent& event) {
		if (event.GetHeight() == 0) {
			return false;
		}
		m_AspectRatio = static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());

		HL_CORE_INFO("The new Aspect Ratio: {}", m_AspectRatio);

		m_Camera.SetProjection(
			-m_AspectRatio * m_ZoomLevel,
			m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel,
			m_ZoomLevel
		);

		return false;
	}

	bool OrthographicCameraController::OnMouseMovedEvent(MouseMovedEvent& event) {
		if (!Input::IsMouseButtonPressed(MouseButton::Right)) {
			m_FirstMouse = true;
			return false;
		}

		float mouseX = event.GetMouseX();

		if (m_FirstMouse) {
			m_LastMouseX = mouseX;
			m_FirstMouse = false;
			return false;
		}

		float deltaX = mouseX - m_LastMouseX;
		m_LastMouseX = mouseX;
		float rotation = m_Camera.GetRotation();
		rotation += deltaX * m_RotationSpeed;
		m_Camera.SetRotation(rotation);
		return false;
	}
}