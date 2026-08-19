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
}