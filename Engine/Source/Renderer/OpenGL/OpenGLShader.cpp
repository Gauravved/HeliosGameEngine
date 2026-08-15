#include<vector>
#include<fstream>
#include<sstream>

#include<glad/gl.h>
#include<glm/gtc/type_ptr.hpp>

#include<Helios/Core/Log.h>
#include<Helios/Renderer/OpenGL/OpenGLShader.h>

namespace Helios {

	// Read file
	std::string OpenGLShader::ReadFile(const std::filesystem::path& path) {
		// Open the file
		std::ifstream file(path);

		if (!file.is_open()) {
			HL_CORE_ERROR("Failed to open shader file: {}", path.string());
			return "";
		}

		std::stringstream stream;

		stream << file.rdbuf();

		return stream.str();
	}


	uint32 CompileShader(GLenum type, const std::string& source) {
		// Return Shader Object ID and creates empty shader
		uint32 shader = glCreateShader(type);

		const char* shaderSource = source.c_str();
		// Uploading shader source
		glShaderSource(
			shader,			// The shader object id create by create shader
			1,				// No. of string to pass most of the cases 1
			&shaderSource,	// OpenGL expects char** hence passing the address of the source itself
			nullptr			// String ends in nullptr or string is null terminated
		);

		// Compiling the created shader
		glCompileShader(shader);

		int isCompiled = 0;
		// To check if the Shader compiled correctly or not
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

		const char* shaderType =
			(type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";

		if (isCompiled == GL_FALSE) {
			// Something went wrong
			int maxLength = 0;
			// get maxlength of the log
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);

			// Retrieve the error
			glGetShaderInfoLog(
				shader,
				maxLength,		// Max Length to write
				&maxLength,		// How many characters it wrote
				infoLog.data()	// Where to write the data
			);

			// Delete the failed shader
			glDeleteShader(shader);

			HL_CORE_ERROR("[{} Shader] \nFailed to Compile \n{}", shaderType, infoLog.data());
	
			return 0;
		}

		HL_CORE_INFO("[{} Shader] \nCompilation Successful", shaderType);

		return shader;
	}

	// To convert compiled shaders to GPU executable programs
	uint32 CreateProgram(uint32 vertexShader, uint32 fragmentShader) {
		// Create an empty program
		uint32 program = glCreateProgram();

		// Attach the vertexShader to program
		glAttachShader(program, vertexShader);

		// Attach the fragmentShader to program
		glAttachShader(program, fragmentShader);

		// Link the program
		/*This is where OpenGL checks things like :
			Does the vertex shader compile ?
			Does the fragment shader compile ?
			Do the outputs of the vertex shader match the inputs of the fragment shader ?
			Are there any interface mismatches ?*/

		glLinkProgram(program);

		int isLinked = 0;

		// Check if program is linked
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			int maxLength = 0;
			// Get Max Length of log
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			//Create vector of length
			std::vector<char> infoLog(maxLength);

			glGetProgramInfoLog(
				program,
				maxLength,
				&maxLength,
				infoLog.data()
			);

			// Delete the unlinked program
			glDeleteProgram(program);

			HL_CORE_ERROR("Failed to link program, \n{}", infoLog.data());

			return 0;
		}

		return program;

	}

	OpenGLShader::OpenGLShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) {
		// Get Source from path
		std::string vertexSource = ReadFile(vertexPath);
		std::string fragmentSource = ReadFile(fragmentPath);

		if (vertexSource.empty() || fragmentSource.empty()) {
			return;
		}

		// Compile Vertex Shader
		uint32 vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);

		if (!vertexShader) {
			return;
		}

		// Compile Fragment Shader
		uint32 fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
		if (!fragmentShader) {
			glDeleteShader(vertexShader);
			return;
		}

		//Create Linked Program
		m_RendererID = CreateProgram(vertexShader, fragmentShader);
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

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
		// Get Uniform Location
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1) {
			HL_CORE_WARN("Uniform '{}' found in shader program {}", name, m_RendererID);
			return;
		}
		// Sent the matrix to OpenGL
		glUniformMatrix4fv(
			location,				// Location of the name
			1,						// Number of matrices we are uploading
			GL_FALSE,				// Should OpenGL transpose the matrix? No, Because GLM and OpenGL both use column-major matrix conventions by default, so the matrix can be uploaded directly.
			glm::value_ptr(value)	// Because OpenGL expects pointer and glm::mat4 is not a pointer
		);

	}

}