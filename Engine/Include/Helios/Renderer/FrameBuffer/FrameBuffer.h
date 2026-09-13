#pragma once

#include<memory>

#include<Helios/Core/Base.h>

namespace Helios {
	class FrameBuffer {
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32 width, uint32 height) = 0;

		virtual uint32 GetColorAttachmentRendererID() const = 0;

		static std::shared_ptr<FrameBuffer> Create(uint32 width, uint32 height);
	};
}