#pragma once

// Since only Windows and Linux OS is supported...
#if defined _WIN32 || defined __CYGWIN__
	#define WINDOWS
#else
	#define LINUX
#endif

#ifdef WINDOWS
	#ifdef BUILDING_STORMBYTE
		#define STORMBYTE_PUBLIC	__declspec(dllexport)
  	#else
      	#define STORMBYTE_PUBLIC	__declspec(dllimport)
  	#endif
  	#define STORMBYTE_PRIVATE
#else
    #define STORMBYTE_PUBLIC		__attribute__ ((visibility ("default")))
    #define STORMBYTE_PRIVATE		__attribute__ ((visibility ("hidden")))
#endif
