#pragma once

#include <glm/glm.hpp>

namespace Helios {
	class Camera {
	public:
		virtual ~Camera() = default;

		const glm::vec4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	protected:
		Camera() = default;

	protected:
		glm::vec4& m_ProjectionMatrix;
	};
}