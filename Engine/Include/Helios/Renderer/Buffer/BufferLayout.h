#pragma once

#include<string>
#include<vector>

#include<Helios/Core/Base.h>

namespace Helios {
	enum class ShaderDataType {
		None = 0,

		Float, // float -> Single Floating point number = 4bytes
		Float2, // vec2 -> 2 Floating point numbers (10.2,10.4) Ususally for 2D positions and UV textures = 8bytes
		Float3, // vec3 - > 3 Floating point numbers ((1.0,2.0,3.0) Used for Positions, Normal, Directions, Colors  = 12bytes
		Float4, // vec4 -> 4 Floating point numbers Used for RGBA, Quaternion, Homogenous co-ordinates = 16 bytes

		Mat3, // mat3 - >3x3 matrix used for normal and rotation= 36bytes
		Mat4, // mat4 - >4x4 matrix used for transforamtion, translation and rotation of 3D objects = 64 bytes

		Int, // Same as float but in integer. Used for Bone ID, InstanceID, Material indices.
		Int2,
		Int3,
		Int4,

		Bool // useful in uniforms and shaders
	};

	static uint32 ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::None:
			return 0;
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Float2:
			return 8;
		case ShaderDataType::Float3:
			return 12;
		case ShaderDataType::Float4:
			return 16;
		case ShaderDataType::Mat3:
			return 36;
		case ShaderDataType::Mat4:
			return 64;
		case ShaderDataType::Int:
			return 4;
		case ShaderDataType::Int2:
			return 8;
		case ShaderDataType::Int3:
			return 12;
		case ShaderDataType::Int4:
			return 16;
		case ShaderDataType::Bool:
			return 1;
		default:
			return 0;
		}
		return 0;
	}


	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32 Size;
		uint32 Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(
			ShaderDataType type,
			const std::string& name,
			bool normalized = false
		) :
			Name(name),
			Type(type),
			Size(ShaderDataTypeSize(type)),
			Offset(0),
			Normalized(normalized) {

		}

		uint32 GetComponentCount() const{
			switch (Type)
			{
			case ShaderDataType::Float:
				return 1;
			case ShaderDataType::Float2:
				return 2;
			case ShaderDataType::Float3:
				return 3;
			case ShaderDataType::Float4:
				return 4;

			case ShaderDataType::Mat3:
				return 3;
			case ShaderDataType::Mat4:
				return 4;

			case ShaderDataType::Int:
				return 1;
			case ShaderDataType::Int2:
				return 2;
			case ShaderDataType::Int3:
				return 3;
			case ShaderDataType::Int4:
				return 4;

			case ShaderDataType::Bool:
				return 1;

			default:
				return 0;
			}
		}
	};

	/*The GPU only sees bytes.BufferLayout tells it :

	Position starts at byte 0
		Color starts at byte 12
		UV starts at byte 24
		Each vertex occupies 32 bytes(the stride)

		Without a BufferLayout, the GPU cannot correctly interpret your vertex data.*/

	class BufferLayout {
	public:
		BufferLayout() = default;

		//instead of list.add() initializer_list can create multiple list elements in one go
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			CalculateOffsetAndStride();
		} 

		const std::vector<BufferElement>& GetElements() const {
			return m_Elements;
		}
		uint32 GetStride() const {
			return m_Stride;
		}

		//Iterator Support
		std::vector<BufferElement>::iterator begin() {
			return m_Elements.begin();
		}
		std::vector<BufferElement>::iterator end() {
			return m_Elements.end();
		}
		std::vector<BufferElement>::const_iterator begin() const {
			return m_Elements.begin();
		}
		std::vector<BufferElement>::const_iterator end() const {
			return m_Elements.end();
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32 m_Stride = 0;

	private:

		void CalculateOffsetAndStride() {
			uint32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	};

}