#pragma once

#include<Helios.h>

class SandboxLayer: public Helios::Layer {
public:
	SandboxLayer();
	~SandboxLayer();
	

	void OnUpdate() override;

private:
	std::shared_ptr<Helios::VertexArray> m_VertexArray;
	std::shared_ptr<Helios::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Helios::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Helios::Shader> m_Shader;
};