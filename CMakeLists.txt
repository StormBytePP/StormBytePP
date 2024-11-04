cmake_minimum_required(VERSION 3.12)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project("StormByte"
	VERSION 0.0.1
	DESCRIPTION "The conveninence StormByte C++ library"
	HOMEPAGE_URL "https://github.com/StormBytePP/StormByte"
)

set(STORMBYTE_DIR ${PROJECT_SOURCE_DIR})
set(STORMBYTE_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${STORMBYTE_CMAKE_DIR})

if(MSVC)
	add_compile_options(/wd4251 /std:c++20 /EHsc /MD)
	add_compile_definitions(UNICODE) # Create problems if disabled
else()
	set(CMAKE_CXX_FLAGS_DEBUG "-pipe -g -ggdb -Wall -Wextra -Wno-unneeded-internal-declaration -Wnon-virtual-dtor -pedantic -pedantic-errors -O0")
endif()

include(Definitions)
add_subdirectory(lib)
add_subdirectory(thirdparty)

if(BUILD_TEST) # This is internal
	add_subdirectory(test)
endif()