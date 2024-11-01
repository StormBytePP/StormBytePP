# Default is off because I'm using features sent by PR not yet officially released
option(WITH_SYSTEM_CONFIG++		"Use system library config++ library"	OFF)

if (STORMBYTE_AS_SUBPROJECT OR WIN32)
	# Forcing bundles on Windows target
	set(WITH_SYSTEM_CONFIG++	OFF)
endif()

add_subdirectory(libconfig++)