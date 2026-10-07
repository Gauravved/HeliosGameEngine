#pragma once

#include<memory>

#include<glm/glm.hpp>

#include<Helios/Core/Base.h>
#include<Helios/Renderer/FrameBuffer/FrameBuffer.h>
#include<Helios/Renderer/Buffer/IndexBuffer.h>
#include<Helios/Renderer/Buffer/VertexBuffer.h>
#include<Helios/Renderer/Buffer/VertexArray.h>
#include<Helios/Renderer/Shader.h>

namespace Helios {
	class SceneRenderer {
	public:
		SceneRenderer(uint32 width, uint32 height);
		~SceneRenderer() = default;

		void Render(const glm::mat4& viewProjection);
		void Resize(uint32 width, uint32 height);

		const std::shared_ptr<FrameBuffer>& GetFrameBuffer() const {
			return m_FrameBuffer;
		}

	private:
		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		std::shared_ptr<Helios::VertexArray> m_VertexArray;
		std::shared_ptr<Helios::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Helios::IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Helios::Shader> m_Shader;

		// GRID specifics
		std::shared_ptr<Helios::VertexArray> m_GridVertexArray;
		std::shared_ptr<Helios::VertexBuffer> m_GridVertexBuffer;
		std::shared_ptr<Helios::IndexBuffer> m_GridIndexBuffer;
		std::shared_ptr<Helios::Shader> m_GridShader;

		std::shared_ptr<Helios::VertexArray> m_BorderVertexArray;
		std::shared_ptr<Helios::VertexBuffer> m_BorderVertexBuffer;
		std::shared_ptr<Helios::IndexBuffer> m_BorderIndexBuffer;

		// Cube positions for the world space
		std::vector<glm::vec3> m_CubePositions = {
			{ 0.0f,  0.0f,  -5.0f },
			{ 5.0f,  0.0f,  -5.0f },
			{ 0.0f,  2.0f,  -8.0f },
			{-3.0f, -1.0f, -10.0f },
			{ 3.0f,  1.0f, -12.0f }
		};
	};
}