// In this class, we make a window and apply functions to the window


#pragma once

#include "SD_PCH.h"

#include "Input.h"
#include "Window.h"

#include "Core.h"

#include "Window.h"
#include "Events/Events.h"
#include "Events/AppEvents.h"

#include "LayerStack.h"


namespace Soda
{
	class SD_DLL App
	{
	public:
		App();
		virtual ~App();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline SodaWindow& GetWindow()
		{ return *m_MainWindow; }

		inline static App& Get()
		{ return *application; }

	private:
		static App* application;
		
		// we want a unique pointer because we dont want to deal with all the deleting shit
		// this is our MainWindow where we do the important stuff (we might have multiple windows later on).
		std::unique_ptr<SodaWindow> m_MainWindow;
		LayerStack m_LayerStack; // this is where are layers will be stored.

		void OnEvent(Event& event);

		bool OnWindowClose(WindowCloseEvent& _WindowCloseEvent);

		bool IsRunning = true; // to check if the App is running or not
	};

	App* CreateApp(); // We create an app that we want to show up on the screen in the main function (start.h)
}