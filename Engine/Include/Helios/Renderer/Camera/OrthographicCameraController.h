#pragma once

#include<Helios/Core/Base.h>
#include<Helios/Core/TimeStep.h>
#include<Helios/Events/MouseEvent.h>
#include<Helios/Events/ApplicationEvent.h>
#include<Helios/Renderer/Camera/OrthographicCamera.h>

namespace Helios {
	class OrthographicCameraController {
	public:
		explicit OrthographicCameraController(float aspectRatio);

		void OnUpdate(TimeStep timeStep);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }


	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnWindowResizedEvent(WindowResizeEvent& event);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		float m_CameraTranslationSpeed = 1.0f;

		OrthographicCamera m_Camera;
	};
}