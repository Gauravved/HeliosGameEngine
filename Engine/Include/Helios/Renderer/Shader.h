#pragma once

#include<memory>
#include<filesystem>

namespace Helios {
	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<Shader> Create(
			const std::filesystem::path& vertexPath,
			const std::filesystem::path& fragmentPath
		);
	};
}