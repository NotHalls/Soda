#include "SD_PCH.h"

#include "WinWindow.h"

#include "Soda/Logger.h"


namespace Soda
{
	static bool s_IsGLFWInitialized = false;

	SodaWindow* SodaWindow::Create(const WindowInfo& windowInfo)
	{
		return new WinWindow(windowInfo);
	}

	WinWindow::WinWindow(const WindowInfo& windowInfo)
	{
		InitWindow(windowInfo);
	}
	WinWindow::~WinWindow()
	{
		CloseWindow();
	}

	void WinWindow::InitWindow(const WindowInfo& windowInfo)
	{
		m_WindowData.Name = windowInfo.Name;
		m_WindowData.Width = windowInfo.Width;
		m_WindowData.Height = windowInfo.Height;

		SD_ENGINE_INFO("Creating Window {0} with dimentions x: {1}, y: {2}", windowInfo.Name, windowInfo.Width, windowInfo.Height);

		if(!s_IsGLFWInitialized)
		{
			int sucess = glfwInit();

			SD_ENGINE_ASSERT(sucess, "Failed to initialize GLFW!");

			s_IsGLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)windowInfo.Width, (int)windowInfo.Height, windowInfo.Name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetVSync(true);
	}

	void WinWindow::CloseWindow()
	{
		glfwDestroyWindow(m_Window);
	}

	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WinWindow::SetVSync(bool status)
	{
		if(status)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_WindowData.VSync = status;
	}

	bool WinWindow::GetVSyncStatus() const
	{
		return m_WindowData.VSync;
	}
}