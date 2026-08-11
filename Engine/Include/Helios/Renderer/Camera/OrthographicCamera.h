#pragma once

#include<Helios/Renderer/Camera/Camera.h>

namespace Helios {

	class OrthographicCamera : public Camera {
	public:
		// Constructor
		explicit OrthographicCamera(float left, float right, float bottom, float top);

		// Destructor
		~OrthographicCamera() override = default;

		// Setter
		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(const glm::vec3& position); // Vec3 because position is 3 dimensional x, y, z
		void SetRotation(float rotation);

		// Getters
		// [[nodiscard]] to tell compiler that "If someone calls this and ignores the result, it might be a mistake."

		[[nodiscard]] const glm::vec3& GetPosition() const;
		[[nodiscard]] float GetRotation() const;

		[[nodiscard]] const glm::mat4& GetViewMatrix() const;
		[[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const;

	private:
		void RecalculateViewMatrix();

	private:
		glm::vec3 m_Position{ 0.0f };
		float m_Rotation = 0.0f;

		glm::mat4 m_ViewMatrix{ 1.0f };
		glm::mat4 m_ViewProjectionMatrix{ 1.0f };
	};
}