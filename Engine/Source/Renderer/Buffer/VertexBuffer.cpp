#include<Helios/Renderer/Buffer/VertexBuffer.h>
#include<Helios/Renderer/Buffer/OpenGLVertexBuffer.h>

namespace Helios {
	std::shared_ptr<VertextBuffer> VertextBuffer::Create(float* vertices, uint32 size) {
		return std::make_shared<OpenGLVertexBuffer>(vertices, size);
	}
}