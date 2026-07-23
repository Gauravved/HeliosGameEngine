#pragma once

#include<memory>

namespace Helios {
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
}

class SandboxLayer {
public:
	SandboxLayer();
	~SandboxLayer();
	

	void OnUpdate();

private:
	std::shared_ptr<Helios::VertexArray> m_VertexArray;
	std::shared_ptr<Helios::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Helios::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Helios::Shader> m_Shader;
};