#include<Helios/Renderer/Buffer/IndexBuffer.h>
#include<Helios/Renderer/RendererAPI.h>
#include<Helios/Renderer/Buffer/OpenGL/OpenGLIndexBuffer.h>

namespace Helios {
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32* indices, uint32 count) {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);

		default:
			return nullptr;
		}
	}
}