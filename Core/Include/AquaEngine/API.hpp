#pragma once

// Platform identification
#if defined(_WIN32)
	#define AQUA_ENGINE_PLATFORM_WINDOWS
	#define PLATFORM_NAME "Windows"
#elif defined(__APPLE__)
	#define AQUA_ENGINE_PLATFORM_APPLE

    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
        // iOS, tvOS, or watchOS device
		#define AQUA_ENGINE_PLATFORM_iOS
		#define PLATFORM_NAME "iOS"
    #elif TARGET_OS_MAC
        // Other kinds of Apple platforms
		#define AQUA_ENGINE_PLATFORM_MAC
		#define PLATFORM_NAME "Mac OS"
    #else
    #   error "Unknown Apple platform"
    #endif
#elif defined(__ANDROID__)
	#define AQUA_ENGINE_PLATFORM_ANDROID
	#define PLATFORM_NAME "Android"
#elif __linux__
	#define AQUA_ENGINE_PLATFORM_LINUX
	#define PLATFORM_NAME "Linux"
#elif defined(__unix__)
	#define AQUA_ENGINE_PLATFORM_UNIX
	#define PLATFORM_NAME "Unix"
#else
	#error "Unknown platform"
#endif

namespace AquaEngine { const char* PlatformName = PLATFORM_NAME; }

#if BUILD_SHARED_LIBS
	#if defined(_MSC_VER)
		#define AQUA_ENGINE_EXPORT __declspec(dllexport)
		#define AQUA_ENGINE_IMPORT __declspec(dllimport)
	#elif defined(__GNUC__)
		#define AQUA_ENGINE_EXPORT __attribute__((visibility("default")))
		#define AQUA_ENGINE_IMPORT
	#else
		#define AQUA_ENGINE_EXPORT
		#define AQUA_ENGINE_IMPORT
	#endif

	#if defined(AQUA_ENGINE_EXPORT_DLL)
		#define AquaAPI AQUA_ENGINE_EXPORT
	#else
		#define AquaAPI AQUA_ENGINE_IMPORT
	#endif
#else
	#define AQUA_ENGINE_EXPORT
	#define AQUA_ENGINE_IMPORT
	#define AquaAPI
#endif

#ifndef AQUA_ENGINE_VERSION_MAJOR
#define AQUA_ENGINE_VERSION_MAJOR 0
#endif
#ifndef AQUA_ENGINE_VERSION_MINOR
#define AQUA_ENGINE_VERSION_MINOR 0
#endif
#ifndef AQUA_ENGINE_VERSION_PATCH
#define AQUA_ENGINE_VERSION_PATCH 0
#endif
#ifndef AQUA_ENGINE_VERSION_REV
#define AQUA_ENGINE_VERSION_REV 0
#endif
#ifndef AQUA_ENGINE_VERSION_BRANCH
#define AQUA_ENGINE_VERSION_BRANCH ""
#endif
