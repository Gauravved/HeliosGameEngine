#include<Helios/Renderer/Buffer/VertexArray.h>
#include<Helios/Renderer/RendererAPI.h>
#include<Helios/Renderer/Buffer/OpenGL/OpenGLVertexArray.h>

namespace Helios {
	std::shared_ptr<VertexArray> VertexArray::Create() {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		default:
			return nullptr;
		}
	}
}