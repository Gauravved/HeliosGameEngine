#include<glm/gtc/matrix_transform.hpp>

#include<Helios/Renderer/Camera/OrthographicCamera.h>

namespace Helios {
	OrthographicCamera::OrthographicCamera(
		float left,
		float right,
		float bottom,
		float top) {
		SetProjection(left, right, bottom, top);
	}

	// Sets the camera projection viewport
	void OrthographicCamera::SetProjection(
		float left, float right,
		float bottom, float top) {
		
		// glm ortho return the projection matrix glm mat4 from the mentioned values
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);

		// AS View Matrix is still valid create the ViewProjection matrix 
		// Cache the combined ViewProjection matrix.
		// Matrices are applied right-to-left, so vertices are transformed:
		// World Space -> View Space -> Clip Space.
		// Hence the multiplication order is Projection * View.
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position) {
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotation) {
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix() {

		glm::mat4 transform = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(m_Rotation),
			glm::vec3(0.0f, 0.0f, 1.0f)
		) * glm::translate(
			glm::mat4(1.0f),
			m_Position
		);

		// The View Matrix is the inverse of the camera transform.
		// Moving the camera right is equivalent to moving the world left.
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	const glm::vec3& OrthographicCamera::GetPosition() const { return m_Position; }
	float OrthographicCamera::GetRotation() const { return m_Rotation; }
	const glm::mat4& OrthographicCamera::GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& OrthographicCamera::GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
}