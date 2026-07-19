#include<Helios/Renderer/Buffer/IndexBuffer.h>
#include<Helios/Renderer/Buffer/OpenGLIndexBuffer.h>

namespace Helios {
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32* indices, uint32 count) {
		return std::make_shared<OpenGLIndexBuffer>(indices, count);
	}
}