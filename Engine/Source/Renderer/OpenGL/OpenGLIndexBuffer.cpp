#include<glad/gl.h>

#include<Helios/Renderer/Buffer/OpenGLIndexBuffer.h>

namespace Helios {
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count):m_Count(count) {
		glCreateBuffers(1, &m_RendererID);
		
		glNamedBufferData(
			m_RendererID,
			count * sizeof(indices),
			indices,
			GL_STATIC_DRAW
			);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


}