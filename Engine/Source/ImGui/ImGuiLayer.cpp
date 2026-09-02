#include<imgui.h>

#include<Helios/ImGui/ImGuiLayer.h>
#include<backends/imgui_impl_win32.h>
#include<backends/imgui_impl_opengl3.h>

namespace Helios {

	ImGuiLayer::ImGuiLayer(void* nativeWindow) : Layer("ImGui"), m_NativeWindow(nativeWindow) {}

	void ImGuiLayer::OnAttach() {
		// Create ImGui's global context and internal state.
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Configure ImGui input/navigation features.
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		// Initialize ImGui's Win32 platform backend.
		ImGui_ImplWin32_Init(m_NativeWindow);

		// Initialize ImGui's OpenGL 3 renderer backend.
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiLayer::OnDetach() {

	}

	void ImGuiLayer::OnUpdate(TimeStep timstep) {
		// Start a new ImGui frame for this engine frame.
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Create a simple test window to verify ImGui integration.
		ImGui::Begin("Helios Editor");
		ImGui::Text("Hello From Helios");
		ImGui::End();

		// Generate ImGui draw commands and submit them through OpenGL
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {

	}
}