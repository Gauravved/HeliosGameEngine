#pragma once

#include<memory>
#include<string>
#include<filesystem>

#include<glm/glm.hpp>

namespace Helios {
	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// This sets Camera ViewProjectionMatrix for rendering vertex shaders in that specific camera matrix
		virtual void SetMat4(
			const std::string& name,
			const glm::mat4& value
		) = 0;

		static std::shared_ptr<Shader> Create(
			const std::filesystem::path& vertexPath,
			const std::filesystem::path& fragmentPath
		);
	};
}