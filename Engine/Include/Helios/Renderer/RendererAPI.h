#pragma once

#include<Helios/Core/Base.h>

namespace Helios {
	class RendererAPI {
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;

		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;
	};
}