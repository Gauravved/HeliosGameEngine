#pragma once

#include<string>

#include<Helios/Core/Base.h>
#include<Helios/Renderer/Shader.h>

namespace Helios {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetMat4(
			const std::string& name,
			const glm::mat4& value
		) override;

	private:
		std::string ReadFile(const std::filesystem::path& path);

	private:
		uint32 m_RendererID;

	};
}