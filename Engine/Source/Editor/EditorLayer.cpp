#include<imgui.h>

#include<Helios/Editor/EditorLayer.h>
#include<Helios/Input/Input.h>

namespace Helios {
	EditorLayer::EditorLayer(const std::shared_ptr<SceneRenderer>& sceneRenderer)
		: Layer("Editor"),
		m_SceneRenderer(sceneRenderer)
	{ }

	EditorLayer::~EditorLayer() {

	}

	void EditorLayer::OnUpdate(TimeStep timeStep) {
		ImGui::Begin("Viewport");

		uint32 textureID = m_SceneRenderer->GetFrameBuffer()->GetColorAttachmentRendererID();

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();

		/*The flipped UV coordinates :
		ImVec2(0.0f, 1.0f),
		ImVec2(1.0f, 0.0f)
		are intentional.OpenGL's framebuffer texture has its vertical orientation opposite to what we want to display in the editor.*/

		ImGui::Image(
			static_cast<ImTextureID>(
				static_cast<uintptr_t>(textureID)
			),
			viewportSize,
			ImVec2(0.0f, 1.0f),
			ImVec2(1.0f, 0.0f)
		);
		// The scene viewport owns mouse input while the cursor
	// is over the rendered scene.
		bool viewportHovered = ImGui::IsItemHovered();
		Input::SetMouseCaptured(!viewportHovered);
		
		ImGui::End();
	}
}