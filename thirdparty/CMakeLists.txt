# Default is off to be used as subproject
option(WITH_SYSTEM_CONFIG++		"Use system config++ library"	OFF)
option(WITH_SYSTEM_SQLITE		"Use system sqlite3 library"	OFF)

add_subdirectory(libconfig++)
add_subdirectory(sqlite3)