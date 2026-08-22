#pragma once

#include<Helios/Renderer/Camera/Camera.h>

namespace Helios {

	class PerspectiveCamera :public Camera {
	public:

		//Constructor
		explicit PerspectiveCamera(
			float fov,
			float aspectRatio,
			float nearClip,
			float farClip
		);

		//Setters
		void SetProjection(
			float fov,
			float aspectRatio,
			float nearClip,
			float farClip
		);

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);

		// Getters
		[[nodiscard]] const glm::vec3& GetPosition() const;
		[[nodiscard]] const glm::vec3& GetRotation() const;

		[[nodiscard]] const glm::mat4& GetViewMatrix() const;
		[[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const;


		glm::vec3 GetForwardDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetUpDirection() const;


		float GetAspectRatio() const { return m_AspectRatio; }
		float GetFOV() const { return m_FOV; }
		float GetNearClip() const { return m_NearClip; }
		float GetFarClip() const { return m_FarClip; }

	private:
		void RecalculateViewMatrix();

		glm::mat4 GetRotationMatrix() const;

	private:
		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;

		glm::vec3 m_Position{ 0.0f };
		glm::vec3 m_Rotation{ 0.0f };
		glm::mat4 m_ViewMatrix{ 1.0f };
		glm::mat4 m_ViewProjectionMatrix{ 1.0f };
	};
}