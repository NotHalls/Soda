#pragma once

#ifdef CT_PLATFORM_WIN
	#ifdef CT_DLL_BUILD
		#define CT_DLL __declspec(dllexport)
	#else
		#define CT_DLL __declspec(dllimport)
	#endif
#else
	#error Sorry bruh... Cotton Engine is only on Windows right now!
#endif
