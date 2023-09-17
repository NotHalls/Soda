#include "SD_PCH.h"

#include "App.h"

#include "Events/Events.h"
#include "Events/AppEvents.h"

#include "Soda/Logger.h"


namespace Soda
{
	App::App()
	{}

	App::~App()
	{}


	void App::Run()
	{
		WindowResizeEvent e(1920, 1080);
		SD_CORE_TRACE(e);

		while(true);
	}
}