#include<Helios/Renderer/FrameBuffer/FrameBuffer.h>
#include<Helios/Renderer/RendererAPI.h>
#include<Helios/Renderer/FrameBuffer/OpenGL/OpenGLFrameBuffer.h>

namespace Helios{
	std::shared_ptr<FrameBuffer> FrameBuffer::Create(uint32 width, uint32 height) {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLFrameBuffer>(width, height);

		default:
			return nullptr;
		}
	}
}