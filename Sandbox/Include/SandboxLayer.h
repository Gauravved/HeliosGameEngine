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

	std::shared_ptr<Helios::VertexArray> m_BorderVertexArray;
	std::shared_ptr<Helios::VertexBuffer> m_BorderVertexBuffer;
	std::shared_ptr<Helios::IndexBuffer> m_BorderIndexBuffer;

	// Cube positions for the world space
	std::vector<glm::vec3> m_CubePositions = {
		{ 0.0f,  0.0f,  -5.0f },
		{ 5.0f,  0.0f,  -5.0f },
		{ 0.0f,  2.0f,  -8.0f },
		{-3.0f, -1.0f, -10.0f },
		{ 3.0f,  1.0f, -12.0f }
	};
};