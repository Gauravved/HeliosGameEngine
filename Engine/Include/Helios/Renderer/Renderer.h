#pragma once 

#include<Helios/Core/Base.h>

namespace Helios {
	class Renderer {
	public:
		static void Init(uint32 width, uint32 height);
		static void BeginFrame();
		static void EndFrame();
		static void OnWindowResize(uint32 width, uint32 height);
	};
}