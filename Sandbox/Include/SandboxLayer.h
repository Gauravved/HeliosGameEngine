#pragma once

#include<Helios.h>

class SandboxLayer : public Helios::Layer {
public:
	explicit SandboxLayer(float aspectRatio);
	~SandboxLayer();


	void OnUpdate(Helios::TimeStep timeStep) override;
	void OnEvent(Helios::Event& event) override;

private:
	// Helios::OrthographicCameraController m_CameraController;
	Helios::PerspectiveCameraController m_CameraController;
	std::shared_ptr<Helios::VertexArray> m_VertexArray;
	std::shared_ptr<Helios::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Helios::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Helios::Shader> m_Shader;

	// GRID specifics
	std::shared_ptr<Helios::VertexArray> m_GridVertexArray;
	std::shared_ptr<Helios::VertexBuffer> m_GridVertexBuffer;
	std::shared_ptr<Helios::IndexBuffer> m_GridIndexBuffer;
	std::shared_ptr<Helios::Shader> m_GridShader;
};