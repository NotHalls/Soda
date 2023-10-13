// In this class, we make a window and apply functions to the window


#pragma once

#include "SD_PCH.h"

#include "Core.h"

#include "Window.h"
#include "Events/Events.h"
#include "Events/AppEvents.h"

#include "LayerStack.h"
#include "Soda/imgui/ImGuiLayer.h"

#include "Renderer/Shaderer.h"
#include "Soda/Renderer/Bufferer.h"
#include "Soda/Renderer/VertexArray.h"


namespace Soda
{
	class App
	{
	public:
		App();
		virtual ~App();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline SodaWindow& GetWindow()
		{ return *m_MainWindow; }

		inline static App& Get()
		{ return *m_app; }

	private:
		static App* m_app;


		
		// we want a unique pointer because we dont want to deal with all the deleting shit
		// this is our MainWindow where we do the important stuff (we might have multiple windows later on).
		std::unique_ptr<SodaWindow> m_MainWindow;
		std::shared_ptr<Shader> m_BasicShader;

		std::shared_ptr<VertexArray> m_VA;
		std::shared_ptr<VertexArray> m_squareVA;

		ImGuiLayer* m_imguiLayer; // the ImGui Layer

		LayerStack m_LayerStack; // this is where are layers will be stored.


		bool OnWindowClose(WindowCloseEvent& _WindowCloseEvent);

		bool IsRunning = true; // to check if the App is running or not
	};

	App* CreateApp(); // We create an app that we want to show up on the screen in the main function (start.h)
}