#include<glm/gtc/matrix_transform.hpp>

#include<Helios/Renderer/Camera/PerspectiveCamera.h>

namespace Helios {
	PerspectiveCamera::PerspectiveCamera(
		float fov,
		float aspectRatio,
		float nearClip,
		float farClip
	) : m_FOV(fov),
		m_AspectRatio(aspectRatio),
		m_NearClip(nearClip),
		m_FarClip(farClip)
	{
		SetProjection(fov, aspectRatio, nearClip, farClip);
		SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
		SetRotation(glm::vec3(-10.0f, 0.0f, 0.0f));
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip) {
		m_FOV = fov;
		m_AspectRatio = aspectRatio;
		m_NearClip = nearClip;
		m_FarClip = farClip;
	    
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position) {
		m_Position = position;
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetRotation(const glm::vec3& rotation) {
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	const glm::vec3& PerspectiveCamera::GetPosition() const { return m_Position; }
	const glm::vec3& PerspectiveCamera::GetRotation() const { return m_Rotation; }
	const glm::mat4& PerspectiveCamera::GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& PerspectiveCamera::GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	void PerspectiveCamera::RecalculateViewMatrix() {
		glm::mat4 rotation = GetRotationMatrix();

		glm::mat4 translation = glm::translate(
			glm::mat4(1.0f),
			m_Position
		);

		glm::mat4 transform = translation * rotation;
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	glm::mat4 PerspectiveCamera::GetRotationMatrix() const {
		glm::mat4 pitch = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(m_Rotation.x),
			glm::vec3(1.0f, 0.0f, 0.0f)
		);
		glm::mat4 yaw = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(m_Rotation.y),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		glm::mat4 roll = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(m_Rotation.z),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);

		return yaw * pitch * roll;
	}

	// Get the camera's forward direction in world space.
	// Direction uses w = 0 so translation does not affect it.
	glm::vec3 PerspectiveCamera::GetForwardDirection() const {
		glm::mat4 rotation = GetRotationMatrix();

		return glm::normalize(
			glm::vec3(
				rotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)
			)
		);
	}

	// Get the camera's right direction in world space.
	// Derived from the camera's local +X axis.
	glm::vec3 PerspectiveCamera::GetRightDirection() const {
		glm::mat4 rotation = GetRotationMatrix();

		return glm::normalize(
			glm::vec3(
				rotation * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
			)
		);
	}

	// Get the camera's up direction in world space.
	// Derived from the camera's local +Y axis.
	glm::vec3 PerspectiveCamera::GetUpDirection() const {
		glm::mat4 rotation = GetRotationMatrix();

		return glm::normalize(
			glm::vec3(
				rotation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)
			)
		);
	}
}