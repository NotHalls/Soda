#pragma once

#include "Soda/Core.h"

#include "Soda/Layers.h"

#include "Soda/Events/AppEvents.h"
#include "Soda/Events/MouseEvents.h"
#include "Soda/Events/KeyboardEvents.h"


namespace Soda
{
	class SD_DLL ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		// dock events
		bool OnWindowResizeEvent(WindowResizeEvent& event);

		// mouse events
		bool OnMouseMoveEvent(MouseMoveEvent& event);
		bool OnMouseScrollEvent(MouseScrollEvent& event);
		bool OnMouseClickEvent(MouseClickedEvent& event);
		bool OnMouseReleaseEvent(MouseReleasedEvent& event);

		// keyboard events
		bool OnKeyPressedEvent(KeyPressEvent& event);
		bool OnKeyReleasedEvent(KeyReleaseEvent& event);
		bool OnKeyTypedEvent(KeyTypeEvent& event);
	private:
		float m_time = 0.0f;
	};
}