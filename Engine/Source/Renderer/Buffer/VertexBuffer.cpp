#include<Helios/Renderer/Buffer/VertexBuffer.h>
#include<Helios/Renderer/RendererAPI.h>
#include<Helios/Renderer/Buffer/OpenGL/OpenGLVertexBuffer.h>

namespace Helios {
	std::shared_ptr<VertextBuffer> VertextBuffer::Create(float* vertices, uint32 size) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);

		default:
			return nullptr;
		}
	}
}