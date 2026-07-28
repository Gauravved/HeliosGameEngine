#pragma once

#include <Windows.h>
#include<Helios/Renderer/GraphicsContext.h>

namespace Helios {
	class OpenGLContext : public GraphicsContext{
	public:
		//explicit contructor in order to avoid the implicit class conversion
		explicit OpenGLContext(HWND windowHandle);
		virtual ~OpenGLContext();

		//Declaring overriding methods
		void Init() override;
		void MakeCurrent() override;
		void SwapBuffer() override;

	private:
		void InitializeDeviceContext();
		void CreateLegacyContext();
		void InitializeWGL();
		void CreateModernContext();
		void InitializeOpenGL();

	private:

		/*
		HWND (The Canvas): The actual window on your screen.

		HDC (The Painter's Toolkit): The Windows device context linked to that window.

		HGLRC (The OpenGL Brain): The OpenGL context that actually processes your 3D math, shaders, and GPU commands.
		*/

		HWND m_Window = nullptr;
		
		///HDC is Handle Device Context: Whenever you want to draw anything on the screen-text, lines, shapes, or images-you cannot just write pixels directly to the monitor. Instead, you have to go through a Device Context.
		HDC m_DeviceContext = nullptr;

		//HGLRC: Handle to an OpenGL Rendering Context.Just like an HDC (Device Context) holds all the state information for standard Windows 2D drawing, an HGLRC holds all the state information for OpenGL 3D drawing.
		//It stores:

		/*OpenGL state
			Current shaders
			Buffers
			Textures
			Pipeline state*/

		HGLRC m_RenderingContext = nullptr;
	};
}