#include<glad/gl.h>

#include<Helios/Renderer/Buffer/OpenGL/OpenGLVertexArray.h>

namespace Helios {


	//Helper function for datatype to OpenGLDataType
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Helios::ShaderDataType::Float:
		case Helios::ShaderDataType::Float2:
		case Helios::ShaderDataType::Float3:
		case Helios::ShaderDataType::Float4:
		case Helios::ShaderDataType::Mat3:
		case Helios::ShaderDataType::Mat4:
			return GL_FLOAT;


		case Helios::ShaderDataType::Int:
		case Helios::ShaderDataType::Int2:
		case Helios::ShaderDataType::Int3:
		case Helios::ShaderDataType::Int4:
			return GL_INT;


		case Helios::ShaderDataType::Bool:
			return GL_BOOL;
		default:
			return 0;
		}
	}

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
		//Get Layout from vertex buffer to interpret it
		const BufferLayout& layout = vertexBuffer->GetLayout();

		//attribute index for later iterations
		uint32 attributeIndex = 0;

		//iterate through the layout
		for (const auto& element : layout) {
			//this function turn on a specific "data pipe" that feeds your 3D model's data into the graphics card's rendering pipeline.
			glEnableVertexAttribArray(attributeIndex);

			//If glEnableVertexAttribArray turns on the "data pipe" for your shader, glVertexAttribPointer is the function that tells OpenGL how to read the data flowing through it.
			glVertexAttribPointer(
				attributeIndex, //Index of the attribute
				element.GetComponentCount(), //The Number of components this element holds
				ShaderDataTypeToOpenGLBaseType(element.Type), //GL Datatype of the components. Currently HardCoded
				element.Normalized ? GL_TRUE : GL_FALSE, //Are the elements normalized
				layout.GetStride(), //The calculated stride for iterations or the value separation
				reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)) //The Offset of current attribute or element (const void*)(uintptr_t)element.Offset
			);
			//A void* is a generic pointer. It holds a memory address, but it has no idea what kind of data lives there. It is just raw memory.

			attributeIndex++;
		}
	}

}
