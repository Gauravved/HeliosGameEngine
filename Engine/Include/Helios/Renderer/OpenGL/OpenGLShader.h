#pragma once

#include<Helios/Core/Base.h>
#include<Helios/Renderer/Shader.h>

namespace Helios {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmenntSource);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

	private:
		uint32 m_RendererID;

	};
}