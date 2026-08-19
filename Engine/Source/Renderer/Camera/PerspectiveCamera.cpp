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
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip) {
		m_FOV = fov;
		m_AspectRatio = aspectRatio;
		m_NearClip = nearClip;
		m_FarClip = farClip;

		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
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


}