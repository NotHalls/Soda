#include "SD_PCH.h"

#include "App.h"

#include "Events/Events.h"
#include "Events/AppEvents.h"

#include "Soda/Logger.h"


namespace Soda
{
	App::App()
	{
		m_MainWindow = std::unique_ptr<SodaWindow>(SodaWindow::Create());
	}

	App::~App()
	{}


	void App::Run()
	{
		while (IsRunning)
		{
			m_MainWindow->OnUpdate();
		}
	}
}