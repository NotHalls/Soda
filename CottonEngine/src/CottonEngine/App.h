#pragma once

#include "Core.h"

namespace CE
{
	class CT_CREATE App
	{
	public:
		App();
		virtual ~App();

		void Run();
	};

	App* CreateApp();
}