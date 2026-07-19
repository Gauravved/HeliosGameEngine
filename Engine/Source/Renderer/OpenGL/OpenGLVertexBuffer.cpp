#include<glad/gl.h>

#include<Helios/Renderer/Buffer/OpenGLVertexBuffer.h>

namespace Helios {
	//This is Direct State Access implementation of OpenGL 4.6 
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32 size) {
		glCreateBuffers(1, &m_RendererID);

		glNamedBufferData(
			m_RendererID,
			size,
			vertices,
			GL_STATIC_DRAW
		);
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}