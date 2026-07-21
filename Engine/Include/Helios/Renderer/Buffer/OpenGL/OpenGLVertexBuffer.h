#pragma once

#include<Helios/Renderer/Buffer/VertexBuffer.h>

namespace Helios {
	class OpenGLVertexBuffer :public VertextBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32 size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override;

	private:
		uint32 m_RendererID;
		BufferLayout m_Layout;
	};
}