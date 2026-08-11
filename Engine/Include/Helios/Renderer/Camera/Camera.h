#pragma once

#include <glm/glm.hpp>

namespace Helios {
	class Camera {
	public:
		virtual ~Camera() = default;

		[[nodiscard]] const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	protected:
		Camera() = default;

	protected:
		glm::mat4 m_ProjectionMatrix{ 1.0f };
	};
}