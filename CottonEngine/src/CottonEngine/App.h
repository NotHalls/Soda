#pragma once

#include "Core.h"

namespace CE
{
	class CT_DLL App
	{
	public:
		App();
		virtual ~App();

		void Run();
	};

	App* CreateApp();
}