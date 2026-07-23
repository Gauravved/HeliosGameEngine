#include<Helios/Renderer/RenderCommand.h>
#include<Helios/Renderer/OpenGL/OpenGLRendererAPI.h>

namespace Helios {
	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

	void RenderCommand::Init() {
		s_RendererAPI->Init();
	}

	void RenderCommand::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) {
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RenderCommand::SetClearColor(float r, float g, float b, float a) {
		s_RendererAPI->SetClearColor(r, g, b, a);
	}

	void RenderCommand::Clear() {
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		s_RendererAPI->DrawIndexed(vertexArray);
	}
}