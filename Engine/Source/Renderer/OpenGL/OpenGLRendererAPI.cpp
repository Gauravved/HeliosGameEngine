#include<glad/gl.h>
#include<glad/wgl.h>

#include<Helios/Renderer/OpenGL/OpenGLRendererAPI.h>

namespace Helios{
	void OpenGLRendererAPI::Init() {
		//Depth Test
		//Why? -> Without depth testing, objects render in the order they're drawn instead of by distance.
		glEnable(GL_DEPTH_TEST);

		//Back-Face Culing
		//Why? -> A cube has 12 triangles. Half of them point away from the camera. The GPU doesn't need to render them. This improves performance and is enabled by default in most engines.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

	}

	void OpenGLRendererAPI::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(float red, float green, float blue, float alpha) {
		/*GLfloat color[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, color);

		std::cout
			<< color[0] << " "
			<< color[1] << " "
			<< color[2] << " "
			<< color[3]
			<< '\n';*/
		glClearColor(red, green, blue, alpha);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*glFinish();

		unsigned char pixel[4] = {};
		GLint readBuffer;
		GLint drawBuffer;

		glGetIntegerv(GL_READ_BUFFER, &readBuffer);
		glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);

		std::cout << "Read Buffer = " << readBuffer << '\n';
		std::cout << "Draw Buffer = " << drawBuffer << '\n';
		glReadPixels(
			0, 0,
			1, 1,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			pixel);

		std::cout
			<< "Pixel = "
			<< (int)pixel[0] << " "
			<< (int)pixel[1] << " "
			<< (int)pixel[2] << " "
			<< (int)pixel[3]
			<< '\n';*/
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		// This tells OpenGL: Use this vertex array configuration for the next draw call.
		vertexArray->Bind();

		// Draw the vertexArray
		glDrawElements(
			GL_TRIANGLES,									// mode. Here it means interpret every 3 indices as triangle
			vertexArray->GetIndexBuffer()->GetCount(),		// count. The number of indices present 
			GL_UNSIGNED_INT,								// type. What is the datatype of the indices
			nullptr											// indices. Start reading indices from the beginning of the currently bound index buffer. If you wanted to start halfway through the buffer, you'd pass an offset instead.
		);
	}

	void OpenGLRendererAPI::DrawLines(const std::shared_ptr<VertexArray>& vertexArray) {
		// Bind the vertex array configuration before drawing.
		vertexArray->Bind();

		// Each pair of indices represents one independent line
		glDrawElements(
			GL_LINES,
			vertexArray->GetIndexBuffer()->GetCount(),
			GL_UNSIGNED_INT,
			nullptr
		);
	}
}