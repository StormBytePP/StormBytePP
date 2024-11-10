#pragma once

// Since only Windows and Linux OS is supported...
#if defined _WIN32 || defined __CYGWIN__
	#define WINDOWS
#else
	#define LINUX
#endif

#ifdef WINDOWS
	#ifdef StormByte_EXPORTS
		#define STORMBYTE_PUBLIC	__declspec(dllexport)
  	#else
      	#define STORMBYTE_PUBLIC	__declspec(dllimport)
  	#endif
  	#define STORMBYTE_PRIVATE
#else
    #define STORMBYTE_PUBLIC		__attribute__ ((visibility ("default")))
    #define STORMBYTE_PRIVATE		__attribute__ ((visibility ("hidden")))
#endif

#if defined(__clang__)
#define CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define GCC
#elif defined(_MSC_VER)
#define MSVC
#endif