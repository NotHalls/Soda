#pragma once

#include "SD_PCH.h"

#include "Window.h"

#include "Core.h"

namespace Soda
{
	class SD_DLL App
	{
	public:
		App();
		virtual ~App();

		void Run();

	private:
		std::unique_ptr<SodaWindow> m_MainWindow;
		bool IsRunning = true;
	};

	App* CreateApp();
}