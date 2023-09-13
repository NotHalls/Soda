#pragma once

#ifdef SD_PLATFORM_WIN
	#ifdef SD_DLL_BUILD
		#define SD_DLL __declspec(dllexport)
	#else
		#define SD_DLL __declspec(dllimport)
	#endif
#else
	#error Sorry bruh... Cotton Engine is only on Windows right now!
#endif
