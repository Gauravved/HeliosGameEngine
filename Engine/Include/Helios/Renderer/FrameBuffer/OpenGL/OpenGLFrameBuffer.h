#pragma once

#include<Helios/Renderer/FrameBuffer/FrameBuffer.h>

namespace Helios {
	class OpenGLFrameBuffer : public FrameBuffer {
	public:

		explicit OpenGLFrameBuffer(uint32 width, uint32 height);
		~OpenGLFrameBuffer();

		void Bind() override;
		void Unbind() override;

		void Resize(uint32 width, uint32 height) override;

		uint32 GetColorAttachmentRendererID() const override;


	private:
		void Invalidate();

	private:
		uint32 m_Width = 0;
		uint32 m_Height = 0;

		uint32 m_RendererID = 0;
		uint32 m_ColorAttachment = 0;
		uint32 m_DepthAttachment = 0;
	};

}