#include<Helios/Renderer/Renderer.h>
#include<Helios/Renderer/RenderCommand.h>


namespace Helios {
	void Renderer::Init(uint32 width, uint32 height) {
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, width, height);
	}
	void Renderer::BeginFrame() {

		RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		RenderCommand::Clear();

	}

	void Renderer::OnWindowResize(uint32 width, uint32 height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::EndFrame() {
		//RenderCommand::Clear();
	}
}