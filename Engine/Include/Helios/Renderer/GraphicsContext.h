#pragma once

namespace Helios {
	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
		//Setup for VULKAN in future implementation
		virtual void MakeCurrent() = 0;
	};
}