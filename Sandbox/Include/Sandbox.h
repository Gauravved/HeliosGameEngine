#pragma once

#include<Helios.h>
#include<SandboxLayer.h>

class Sandbox : public Helios::Application {
public:
	Sandbox() {
		float aspectRatio = static_cast<float>(GetWindow().GetWidth()) / static_cast<float>(GetWindow().GetHeight());
		PushLayer(std::make_shared<SandboxLayer>(aspectRatio));
	}
};