#pragma once

// Since only Windows and Linux OS is supported...
#if defined _WIN32 || defined __CYGWIN__
	#define WINDOWS
#else
	#define LINUX
#endif

#ifdef WINDOWS
	#ifdef Alchemy_EXPORTS
		#define DLL_PUBLIC	__declspec(dllexport)
  	#else
      	#define DLL_PUBLIC	__declspec(dllimport)
  	#endif
  	#define DLL_LOCAL
#else
    #define DLL_PUBLIC		__attribute__ ((visibility ("default")))
    #define DLL_LOCAL		__attribute__ ((visibility ("hidden")))
#endif
