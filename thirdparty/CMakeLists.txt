include(CMakeDependentOption)

# Default is off to be used as subproject
option(ENABLE_SQLITE							"Enable SQLite"					ON)
cmake_dependent_option(WITH_SYSTEM_SQLITE		"Use system sqlite3 library"	OFF ENABLE_SQLITE ON)

add_subdirectory(sqlite3)