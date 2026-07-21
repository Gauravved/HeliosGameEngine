#include<Helios/Renderer/Shader.h>
#include<Helios/Renderer/RendererAPI.h>
#include<Helios/Renderer/OpenGL/OpenGLShader.h>

namespace Helios {
	std::shared_ptr<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);

		default:
			return nullptr;
		}
	}
}