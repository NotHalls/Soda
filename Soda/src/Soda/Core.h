#pragma once

#define BIT(x) (1 << x)

#ifdef SD_PLATFORM_WIN
	#ifdef SD_DLL_BUILD
		#define SD_DLL __declspec(dllexport)
	#else
		#define SD_DLL __declspec(dllimport)
	#endif
#else
	#error Sorry bruh... Cotton Engine is only on Windows right now!
#endif

#ifdef SD_ENABLE_ASSERTS
	#define SD_ASSERT(x, ...)\
		if(!(x))\
		{\
			SD_ERROR("ERRORRR... while asserting {0}", __VA_ARGS__);\
			__debugbreak();\
		}
	#define SD_ENGINE_ASSERT(x, ...)\
		if(!(x))\
		{\
			SD_ENGINE_ERROR("ERRORRR... while asserting {0}", __VA_ARGS__);\
			__debugbreak();\
		}
#else
	#define SD_ASSERT(x, ...)
	#define SD_ENGINE_ASSERT(x, ...)
#endif