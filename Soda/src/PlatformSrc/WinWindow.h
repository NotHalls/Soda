#pragma once

#include "Soda/Window.h"

#include "GLFW/glfw3.h"


namespace Soda
{
	class WinWindow : public SodaWindow
	{
	public:
		WinWindow(const WindowInfo& windowInfo);
		virtual ~WinWindow();

		void OnUpdate() override;

		inline unsigned int GetWindowWidth() const override
		{ return m_WindowData.Width; }
		inline unsigned int GetWindowHeight() const override
		{ return m_WindowData.Height; }

		void SetCallbackFn(const EventCallbackFn& CallbackFn) override
		{ m_WindowData.CallbackFn = CallbackFn; }

		void SetVSync(bool status) override;
		bool GetVSyncStatus() const override;


	private:
		virtual void InitWindow(const WindowInfo& windowInfo);
		virtual void CloseWindow();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Name;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn CallbackFn;
		};

		WindowData m_WindowData;
	};
}