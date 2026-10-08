#pragma once

#include<Helios/Core/Layer.h>
#include<Helios/Renderer/SceneRenderer/SceneRenderer.h>

namespace Helios {

	class EditorLayer :public Layer {
	public:
		explicit EditorLayer(const std::shared_ptr<SceneRenderer>& sceneRenderer);
		~EditorLayer() override;

		void OnUpdate(TimeStep timeStep) override;

	private:
		std::shared_ptr<SceneRenderer> m_SceneRenderer;
	};
}