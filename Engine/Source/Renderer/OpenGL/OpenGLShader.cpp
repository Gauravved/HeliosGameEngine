#include<vector>

#include<glad/gl.h>

#include<Helios/Renderer/OpenGL/OpenGLShader.h>

namespace Helios {
	uint32 CompileShader(GLenum type, const std::string& source) {
		//Return Shader Object ID and creates empty shader
		uint32 shader = glCreateShader(type);

		const char* shaderSource = source.c_str();
		//Binding shader source
		glShaderSource(
			shader, //The shader object id create by create shader
			1, //No. of string to pass most of the cases 1
			&shaderSource, //OpenGL expects char** hence passing the address of the source itself
			nullptr //String ends in nullptr or string is null terminated
		);

		//Compiling the created shader
		glCompileShader(shader);

		int isCompiled = 0;
		//To check if the Shader compiled correctly or not
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			//Something went wrong
			int maxLength = 0;
			//get maxlength of the log
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);

			//Retrieve the error
			glGetShaderInfoLog(
				shader,
				maxLength, //Max Length to write
				&maxLength, //How many characters it wrote
				infoLog.data() //Where to write the data
			);
			//Delete the failed shader
			glDeleteShader(shader);

			return 0;
		}

		return shader;
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {
		
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

}