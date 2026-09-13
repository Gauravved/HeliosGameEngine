#include<glad/gl.h>

#include<Helios/Core/Log.h>
#include<Helios/Renderer/FrameBuffer/OpenGL/OpenGLFrameBuffer.h>

// Framebuffers provide an off-screen rendering target.
// The scene is rendered into a color texture instead of directly
// to the screen, allowing the result to be displayed and processed
// elsewhere, such as the ImGui editor viewport.

namespace Helios {
	OpenGLFrameBuffer::OpenGLFrameBuffer(uint32 width, uint32 height)
		:m_Width(width),
		m_Height(height) {

		Invalidate();
	}

	// Build/Create the frambuffer and add the attachments
	void OpenGLFrameBuffer::Invalidate() {
		// Generate and Bind FrameBuffers
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		HL_CORE_INFO("OpenGL FrameBuffer created: {}x{} (ID: {}", m_Width, m_Height, m_RendererID);

		// Color Attachments

		// Create an OpenGL texture that will store the rendered color data.
		// This texture will later be passed to ImGui so the editor can display
		// the rendered scene inside the viewport.
		glGenTextures(1, &m_ColorAttachment);

		// Make these textures active 2D textures
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

		// Allocate GPU storage for the color texture.
		// No initial pixel data is provided because the renderer will fill
		// this texture when the framebuffer is used as a render target.
		glTexImage2D(
			GL_TEXTURE_2D,						// Texture target
			0,									// Mipmap level: 0 is base level 
			GL_RGBA8,							// Internal Format: 8 bits for each RGBA channel
			static_cast<GLsizei>(m_Width),		// Width of the texture in pixel
			static_cast<GLsizei>(m_Height),		// Height of the texture in pixel
			0,									// Border: must be 0 in mordern OpenGL
			GL_RGBA,							// Format of supplied pixel data
			GL_UNSIGNED_BYTE,					// Data type of each color channel
			nullptr								// No initial pixel data, renderring will fill the textures
		);

		// Use linear filtering when the framebuffer texture is sampled at
		// a different size than its original resolution.

		glTexParameteri(
			GL_TEXTURE_2D,				// Texture target
			GL_TEXTURE_MIN_FILTER,		// Filtering use when the texture is displayed smaller
			GL_LINEAR					// Linearly interpolate neighbouring pixels
		);

		glTexParameteri(
			GL_TEXTURE_2D,				// Texture target
			GL_TEXTURE_MAG_FILTER,		// Filtering use when the texture is displayed larger
			GL_LINEAR					// Linearly interpolate neighbouring pixels
		);


		// Clamp texture coordinates to the edge of the texture.
		// This prevents sampling outside the viewport texture from wrapping
		// around to the opposite side.

		glTexParameteri(
			GL_TEXTURE_2D,				// Texture target
			GL_TEXTURE_WRAP_S,			// Wrapping behavior along the horizaontal axis
			GL_LINEAR					// Linearly interpolate neighbouring pixels
		);

		glTexParameteri(
			GL_TEXTURE_2D,				// Texture target
			GL_TEXTURE_WRAP_T,			// Wrapping behavior along the vertical axis
			GL_LINEAR					// Linearly interpolate neighbouring pixels
		);


		// Attach the color texture to the framebuffer's first color attachment.
		// Rendering performed while this framebuffer is bound will write its
		// final color output into this texture.
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,				// FramBuffer currently being configured
			GL_COLOR_ATTACHMENT0,		// First color attachment
			GL_TEXTURE_2D,				// Type of resource being attached
			m_ColorAttachment,			// Color Texture to attach
			0							// Mipmap level: 0 is the base level
		);


		// Depth + stencil attachment
		// Create a renderbuffer for depth and stencil data.
		// We do not need to sample this data later, so a renderbuffer is
		// sufficient for our current framebuffer implementation.
		glGenRenderbuffers(1, &m_DepthAttachment);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment);


		// Allocate storage for both depth and stencil information.
		// The dimensions match the color attachment so that both attachments
		// cover the same rendering area.
		glRenderbufferStorage(
			GL_RENDERBUFFER,					// RenderBuffer target
			GL_DEPTH24_STENCIL8,				// Setting 24-bit depth + 8-bit stencil format
			static_cast<GLsizei>(m_Width),		// Width of RenderBuffer in pixel
			static_cast<GLsizei>(m_Height)		// Height of RenderBuffer in pixel
		);


		// Attach the depth/stencil renderbuffer to the framebuffer.
		// This allows our existing depth testing to continue working while the
		// scene is rendered into the off-screen framebuffer.
		glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,						// FrameBuffer currently being configured
			GL_DEPTH_STENCIL_ATTACHMENT,		// Attachment point for depth + stencil data
			GL_RENDERBUFFER,					// Type of resource being ttached
			m_DepthAttachment					// RenderBuffer to attach
		);


		// Ask OpenGL whether all required framebuffer attachments have been
		// configured correctly and the framebuffer is ready for rendering.
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			HL_CORE_ERROR(
				"OpenGL FrameBuffer is incomplete: {}x{} (ID: {})",
				m_Width,
				m_Height,
				m_RendererID
			);
		}
		else {
			HL_CORE_INFO(
				"OpenGL FrameBuffer is complete: {}x{} (ID: {})",
				m_Width,
				m_Height,
				m_RendererID
			);
		}


		// Restore the default window framebuffer so framebuffer creation does not
		// leave our off-screen framebuffer bound for unrelated rendering.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

}