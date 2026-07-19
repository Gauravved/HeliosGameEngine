#pragma once

#include<memory>

#include<Helios/Core/Base.h>

namespace Helios {
	class VertextBuffer {
	public:
		virtual ~VertextBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<VertextBuffer> Create(float* vertics, uint32 size);

	};
}