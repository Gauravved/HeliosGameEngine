#include<Helios/Renderer/Camera/PerspectiveCameraController.h>
#include<Helios/Input/Input.h>
#include<Helios/Core/Log.h>

namespace Helios {
	PerspectiveCameraController::PerspectiveCameraController(
		float fov,
		float aspectRatio,
		float nearClip,
		float farClip
	) :m_Camera(fov, aspectRatio, nearClip, farClip) {

	}
}