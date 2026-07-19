#include<glad/gl.h>

#include<Helios/Renderer/Buffer/OpenGLVertexArray.h>

namespace Helios {
	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		Bind();
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const {
		return m_IndexBuffer;
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertextBuffer>& vertexBuffer) {
		Bind();
		vertexBuffer->Bind();
	}
}
