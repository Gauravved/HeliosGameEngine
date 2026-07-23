
#include<stdexcept>
//#include<iostream>

#include<glad/gl.h>
#include<glad/wgl.h>

#include<Helios/Core/Log.h>
#include<Helios//Renderer/OpenGL/OpenGLContext.h>
#include<Helios/Renderer/OpenGL/OpenGLConfig.h>


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

	void OpenGLContext::InitializeDeviceContext() {
		m_DeviceContext = GetDC(m_Window);

		if (!m_DeviceContext) {
			HL_CORE_ERROR("Failed to get device context");
			throw std::runtime_error("Failed to get device context");
		}

		PIXELFORMATDESCRIPTOR pixelFormat{};

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

		if (pixelFormatIndex == 0) {
			HL_CORE_ERROR("ChoosePixelFormat Failed");
			throw std::runtime_error("ChoosePixelFormat Failed");
		}

		if (!SetPixelFormat(m_DeviceContext, pixelFormatIndex, &pixelFormat)) {
			HL_CORE_ERROR("Failed to set pixel format");
			throw std::runtime_error("Failed to set pixel format");
		}
		HL_CORE_INFO("HWND created: {}",static_cast<void*>(m_Window));
		HL_CORE_INFO("HDC creatd: {}", static_cast<void*>(m_DeviceContext));

	}

	void OpenGLContext::CreateLegacyContext() {
		//Create Renderer context for 3D 
		m_RenderingContext = wglCreateContext(m_DeviceContext);

		if (!m_RenderingContext) {
			HL_CORE_ERROR("Failed to create OpenGL context");
			throw std::runtime_error("Failed to create OpenGL Context");
		}

		if (!wglMakeCurrent(m_DeviceContext, m_RenderingContext)) {
			HL_CORE_ERROR("Failed to activate current OpenGL");
			throw std::runtime_error("Failed to activate Current OpenGL");
		}
	}

	void OpenGLContext::InitializeWGL() {
		int version = gladLoaderLoadWGL(m_DeviceContext);

		if (0 == version) {
			HL_CORE_ERROR("Failed to initialieze WGL");
			throw std::runtime_error("Failed to initialize WGL");
		}
	}

	void OpenGLContext::CreateModernContext() {
		//Defining context attributes for the WGL ATTRIARB
		const int contextAttributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, OpenGLConfig::MajorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB, OpenGLConfig::MinorVersion,

			GL_CONTEXT_PROFILE_MASK,
			GL_CONTEXT_CORE_PROFILE_BIT,

#ifdef _DEBUG
			WGL_CONTEXT_FLAGS_ARB,
			WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0
		};

		//Create new context
		HGLRC modernContext = wglCreateContextAttribsARB(m_DeviceContext, nullptr, contextAttributes);

		////Check status
		if (!modernContext) {
			HL_CORE_ERROR("Failed to create OpenGL 4.6 Core Profile");
			throw std::runtime_error("Failed to create OpenGL 4.6 Core Profile");
		}

		//Detach the Leagacy context
		wglMakeCurrent(nullptr, nullptr);

		//Destroy the legacy context
		wglDeleteContext(m_RenderingContext);

		//Store modern context
		m_RenderingContext = modernContext;

		//Acttivate Modern Context
		if (!wglMakeCurrent(m_DeviceContext, m_RenderingContext)) {
			HL_CORE_ERROR("Failed to activate OpenGL 4.6 context");
			throw std::runtime_error("Failed to activate OpenGL 4.6 context");
		}



	}

	void OpenGLContext::InitializeOpenGL() {
		int version = gladLoaderLoadGL();

		if (0 == version) {
			HL_ERROR("Failed to initialize OpenGL");
			throw std::runtime_error("Failed to initialize OpenGL");
		}

		//Just check that everything is working fine
		const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		const char* versionString = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		const char* glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (!vendor || !renderer || !versionString || !glslVersion)
		{
			throw std::runtime_error("Failed to query OpenGL information.");
		}

		HL_CORE_INFO("----------------------------------");
		HL_CORE_INFO("Helios Renderer Initialized");
		HL_CORE_INFO("Vendor   : {}", vendor);
		HL_CORE_INFO("Renderer : {}", renderer);
		HL_CORE_INFO("OpenGL   : {}", versionString);
		HL_CORE_INFO("GLSL     : {}", glslVersion);
		HL_CORE_INFO("----------------------------------");

		if (wglSwapIntervalEXT) {
			wglSwapIntervalEXT(1);
		}
	}

	void OpenGLContext::Init() {
		
		InitializeDeviceContext();

		CreateLegacyContext();

		InitializeWGL();

		CreateModernContext();

		InitializeOpenGL();


	}

	//MakeCurrent
	void OpenGLContext::MakeCurrent() {
		wglMakeCurrent(m_DeviceContext, m_RenderingContext);
	}

	//Swap Buffer
	void OpenGLContext::SwapBuffer() {
		/*GLint drawBuffer = 0;
		glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
		std::cout << "Current HWND = " << GetForegroundWindow() << '\n';
		std::cout << "My HWND      = " << m_Window << '\n';*/

		//std::cout << "Draw Buffer: " << drawBuffer << '\n';
		// Windows already has a function name
		BOOL result = ::SwapBuffers(m_DeviceContext);
		/*std::cout << "Swap Result: " << result << std::endl;*/

		if (!result)
		{
			HL_CORE_ERROR("GLContextFailed SwapBuffer: {}", GetLastError());
		}
	}

}