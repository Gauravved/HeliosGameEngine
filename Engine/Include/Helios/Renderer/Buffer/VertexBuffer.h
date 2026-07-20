#pragma once

#include<memory>

#include<Helios/Core/Base.h>
#include<Helios/Renderer/Buffer/BufferLayout.h>

namespace Helios {
	class VertextBuffer {
	public:
		virtual ~VertextBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static std::shared_ptr<VertextBuffer> Create(float* vertics, uint32 size);

	};
}