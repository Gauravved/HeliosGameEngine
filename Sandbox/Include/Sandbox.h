#pragma once

#include<Helios.h>
#include<SandboxLayer.h>

class Sandbox : public Helios::Application {
public:
	Sandbox() {
		float aspectRatio = static_cast<float>(GetWindow().GetWidth()) / static_cast<float>(GetWindow().GetHeight()); 
		auto scenerRenderer = std::make_shared<Helios::SceneRenderer>(GetWindow().GetWidth(), GetWindow().GetHeight());

		auto sandboxLayer = std::make_shared<SandboxLayer>(aspectRatio, scenerRenderer);
		auto editorLayer = std::make_shared<Helios::EditorLayer>(scenerRenderer);

		PushLayer(sandboxLayer);
		PushLayer(editorLayer);
	}
};