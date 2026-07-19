#pragma once

#include<Helios/Renderer/Buffer/VertexBuffer.h>

namespace Helios {
	class OpenGLVertexBuffer :public VertextBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32 size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

	private:
		uint32 m_RendererID;
	};
}