#pragma once

#include<memory>

#include<Helios/Renderer/RendererAPI.h>

namespace Helios {
	class RenderCommand {
	public:
		static void Init();

		static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
		static void DrawLines(const std::shared_ptr<VertexArray>& vertexArray);
	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;

	};
}