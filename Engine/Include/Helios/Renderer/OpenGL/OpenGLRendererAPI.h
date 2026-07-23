#pragma once

#include<Helios/Renderer/RendererAPI.h>

namespace Helios {
	class OpenGLRendererAPI : public RendererAPI{
	public:
		virtual ~OpenGLRendererAPI() = default;

		virtual void Init() override;

		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;
		virtual void SetClearColor(float r, float g, float b, float a) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}