#pragma once

#include "Core.h"

namespace Soda
{
	class SD_DLL App
	{
	public:
		App();
		virtual ~App();

		void Run();
	};

	App* CreateApp();
}