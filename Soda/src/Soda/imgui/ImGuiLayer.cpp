#include "SD_PCH.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "PlatformSrc/OpenGL/imgui_impl_opengl3.h"

#include "Soda/Core.h"

#include "Soda/App.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Soda
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}


	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsClassic();

		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		imguiIO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// This is temporary... we will have Soda keybindigns later on.
		imguiIO.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		imguiIO.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		imguiIO.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		imguiIO.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		imguiIO.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;

		imguiIO.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		imguiIO.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;

		imguiIO.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		imguiIO.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		imguiIO.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		imguiIO.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;

		imguiIO.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;		
		imguiIO.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		imguiIO.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		imguiIO.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		imguiIO.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;

		imguiIO.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		imguiIO.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		imguiIO.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		imguiIO.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		imguiIO.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		imguiIO.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	
    void ImGuiLayer::OnDetach()
	{

	}


	void ImGuiLayer::OnUpdate()
	{
		App& app = App::Get();
		ImGuiIO& imguiIO = ImGui::GetIO();

		
		imguiIO.DisplaySize = ImVec2(app.GetWindow().GetWindowWidth(), app.GetWindow().GetWindowHeight());

		float time = (float)glfwGetTime();
		imguiIO.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		// dock events
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(ImGuiLayer::OnWindowResizeEvent));
		
		// mouse events
		dispatcher.Dispatch<MouseMoveEvent>(BIND_FN(ImGuiLayer::OnMouseMoveEvent));
		dispatcher.Dispatch<MouseScrollEvent>(BIND_FN(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.Dispatch<MouseClickedEvent>(BIND_FN(ImGuiLayer::OnMouseClickEvent));
		dispatcher.Dispatch<MouseReleasedEvent>(BIND_FN(ImGuiLayer::OnMouseReleaseEvent));

		// keyboard events
		dispatcher.Dispatch<KeyPressEvent>(BIND_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleaseEvent>(BIND_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypeEvent>(BIND_FN(ImGuiLayer::OnKeyTypedEvent));
	}


	
	// these are all the events related to out ui
	
	// dock events
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.DisplaySize = ImVec2(event.GetWindowWidth(), event.GetWindowHeight());

		// imguiIO.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		// glViewport(0, 0, event.GetWindowWidth(), event.GetWindowHeight());

		return false;
	}


	// mouse events
	bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.MousePos = ImVec2(event.GetMouseX(), event.GetMouseY());

		return false;
	}
	
	bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.MouseWheelH += event.GetWheelOffsetX();
		imguiIO.MouseWheel += event.GetWheelOffsetY();

		return false;
	}

	bool ImGuiLayer::OnMouseClickEvent(MouseClickedEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.MouseDown[event.GetButtonClicked()] = true;

		SD_ENGINE_INFO(imguiIO.KeyMap[event.GetButtonClicked()]);

		return false;
	}

	bool ImGuiLayer::OnMouseReleaseEvent(MouseReleasedEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.MouseDown[event.GetButtonClicked()] = false;

		return false;
	}


	// keyboard events
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.KeysDown[event.GetKeyCode()] = true;

		imguiIO.KeyCtrl = imguiIO.KeysDown[GLFW_KEY_LEFT_CONTROL] || imguiIO.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		imguiIO.KeyShift = imguiIO.KeysDown[GLFW_KEY_LEFT_SHIFT] || imguiIO.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		imguiIO.KeyAlt = imguiIO.KeysDown[GLFW_KEY_LEFT_ALT] || imguiIO.KeysDown[GLFW_KEY_RIGHT_ALT];
		imguiIO.KeySuper = imguiIO.KeysDown[GLFW_KEY_LEFT_SUPER] || imguiIO.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleaseEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		imguiIO.KeysDown[event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypeEvent& event)
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		int character = event.GetKeyCode();

		if(character > 0 && character < 0x10000)
			imguiIO.AddInputCharacter((unsigned short)character);

		return false;
	}

}