#pragma once

#include<Helios/Renderer/Buffer/IndexBuffer.h>

namespace Helios {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32* indices, uint32 count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		uint32 GetCount() const override {
			return m_Count;
		}

	private:
		uint32 m_RendererID;
		uint32 m_Count;

	};
}