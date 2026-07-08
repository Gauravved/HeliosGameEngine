#include<Helios//Renderer/OpenGLContext.h>

#include<stdexcept>

namespace Helios {
	OpenGLContext::OpenGLContext(HWND windowHandle) : m_Window(windowHandle){}

	//this destructor (for now) prevents windowsd resource from leaking
	OpenGLContext::~OpenGLContext() {
		if (m_RenderingContext) {
			wglDeleteContext(m_RenderingContext);
		}
		if (m_DeviceContext) {
			ReleaseDC(m_Window, m_DeviceContext);
		}
	}

	void OpenGLContext::Init() {
		m_DeviceContext = GetDC(m_Window);

		if (!m_DeviceContext) {
			throw std::runtime_error("Failed to get device context");
		}

		PIXELFORMATDESCRIPTOR pixelFormat;

		pixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormat.nVersion = 1;

		pixelFormat.dwFlags =
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER;

		pixelFormat.iPixelType = PFD_TYPE_RGBA;

		pixelFormat.cColorBits = 32;
		pixelFormat.cDepthBits = 24;
		pixelFormat.cStencilBits = 8;

		pixelFormat.iLayerType = PFD_MAIN_PLANE;

		//Asking windows which pizel format is best for these specs
		int pixelFormatIndex = ChoosePixelFormat(m_DeviceContext, &pixelFormat);

		if (!SetPixelFormat(m_DeviceContext, pixelFormatIndex, &pixelFormat)) {
			throw std::runtime_error("Failed to set pixel format");
		}

		//Create Renderer context for 3D 
		m_RenderingContext = wglCreateContext(m_DeviceContext);

		if (!m_RenderingContext) {
			throw std::runtime_error("Failed to create OpenGL Context");
		}

		if (!wglMakeCurrent(m_DeviceContext, m_RenderingContext)) {
			throw std::runtime_error("Failed to activate Current OpenGL");
		}


	}

	//MakeCurrent
	void OpenGLContext::MakeCurrent() {
		wglMakeCurrent(m_DeviceContext, m_RenderingContext);
	}

	//Swap Buffer
	void OpenGLContext::SwapBuffer() {
		// Windows already has a function name
		::SwapBuffers(m_DeviceContext);
	}

}