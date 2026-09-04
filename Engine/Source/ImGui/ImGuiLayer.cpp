#include<imgui.h>
#include<backends/imgui_impl_win32.h>
#include<backends/imgui_impl_opengl3.h>

#include<Helios/ImGui/ImGuiLayer.h>
#include<Helios/Core/Log.h>

namespace Helios {

	ImGuiLayer::ImGuiLayer(void* nativeWindow) : Layer("ImGui"), m_NativeWindow(nativeWindow) {}
	ImGuiLayer::~ImGuiLayer() {
		HL_CORE_INFO("ImGuiLayer (Overlay) Destroyed");
	}

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
		// Shutdown OpenGL3 and Win32
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();

		// Destroy Context
		ImGui::DestroyContext();

		HL_CORE_INFO("ImGui Layer (Overlay) Detached");
	}

	void ImGuiLayer::OnUpdate(TimeStep timstep) {
		// Start a new ImGui frame for this engine frame.
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Create a simple test window to verify ImGui integration.
		/*ImGui::Begin("Helios Editor");

		ImGui::Text("Hello from Helios!");

		static bool showDemo = false;

		if (ImGui::Button("Open ImGui Demo")) {
			showDemo = true;
		}

		if (showDemo) {
			ImGui::ShowDemoWindow(&showDemo);
		}

		ImGui::End();*/

		ImGui::SetNextWindowSize(ImVec2(500.0f, 300.0f));

		ImGui::Begin("Helios Editor");

		ImGui::Text("Hello from Helios!");

		static char textBuffer[256] = "";

		ImGui::InputText("Test Input", textBuffer, sizeof(textBuffer));

		ImGui::End();

		// Generate ImGui draw commands and submit them through OpenGL
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {
		ImGuiIO& io = ImGui::GetIO();

		if (event.IsInCategory(EventCategoryMouse)) {
			event.Handled |= io.WantCaptureMouse;
		}
		if (event.IsInCategory(EventCategoryKeyboard)) {
			event.Handled |= io.WantCaptureKeyboard;
		}

	}
}