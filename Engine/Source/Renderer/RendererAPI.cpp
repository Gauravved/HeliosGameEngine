#include<Helios/Renderer/RendererAPI.h>
#include<Helios/Renderer/OpenGL/OpenGLRendererAPI.h>

namespace Helios {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	std::unique_ptr<RendererAPI> RendererAPI::Create() {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLRendererAPI>();
		default:
			return nullptr;
		}
	}
}