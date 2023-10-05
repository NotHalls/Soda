#pragma once

#include "Soda/Core.h"

#include "Soda/Layers.h"

#include "Soda/Events/AppEvents.h"
#include "Soda/Events/MouseEvents.h"
#include "Soda/Events/KeyboardEvents.h"


namespace Soda
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_time = 0.0f;
	};
}