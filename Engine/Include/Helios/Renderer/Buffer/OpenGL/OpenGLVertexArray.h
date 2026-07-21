#pragma once

#include<Helios/Renderer/Buffer/VertexArray.h>

namespace Helios {
	class OpenGLVertexArray :public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<VertextBuffer>& vertexBuffer) override;
		
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

	private:
		uint32 m_RendererID;

		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
}