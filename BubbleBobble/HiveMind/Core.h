#pragma once
#ifdef HM_PLATFORM_WINDOWS
	#ifdef HM_BUILD_DLL
		#define HIVEMIND_API __declspec(dllexport)
	#else
		#define HIVEMIND_API __declspec(dllimport)
	#endif
#else
	#error HiveMind only supported on Windows
#endif