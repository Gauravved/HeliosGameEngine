#pragma once

#include<Helios/Core/Base.h>
#include<Helios/Renderer/Buffer/VertexArray.h>

namespace Helios {
	class RendererAPI {
	public:

		enum class API {
			None = 0,
			OpenGL
		};

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;

		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static API GetAPI() {
			return s_API;
		}

		static std::unique_ptr<RendererAPI> Create();

	private:
		static API s_API;
	};
}