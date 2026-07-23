#include<Helios/Renderer/Shader.h>
#include<Helios/Renderer/RendererAPI.h>
#include<Helios/Renderer/OpenGL/OpenGLShader.h>

namespace Helios {
	std::shared_ptr<Shader> Shader::Create(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexPath, fragmentPath);

		default:
			return nullptr;
		}
	}
}