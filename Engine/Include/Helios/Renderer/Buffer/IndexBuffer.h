#pragma once

#include<memory>

#include<Helios/Core/Base.h>

namespace Helios {
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(uint32* indices, uint32 count);
	};
}