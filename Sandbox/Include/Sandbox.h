#pragma once

#include<Helios.h>
#include<SandboxLayer.h>

class Sandbox : public Helios::Application {
public:
	Sandbox() {
		PushLayer(std::make_shared<SandboxLayer>());
	}
};