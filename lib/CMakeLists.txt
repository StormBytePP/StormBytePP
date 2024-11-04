include(GNUInstallDirs)
file (GLOB STORMBYTE_SOURCES ${STORMBYTE_DIR}/lib/*.cxx ${STORMBYTE_DIR}/lib/**/*.cxx)

# SQLite support
set(STORMBYTE_SQLITE_SOURCES
	${STORMBYTE_DIR}/lib/sqlite3.cxx
)

if (NOT STORMBYTE_AS_SUBPROJECT OR WIN32)
	add_library(StormByte SHARED ${STORMBYTE_SOURCES} ${STORMBYTE_HEADERS})
else()
	add_library(StormByte STATIC ${STORMBYTE_SOURCES})
endif()
target_compile_definitions(StormByte PRIVATE BUILDING_STORMBYTE)
set_target_properties(StormByte PROPERTIES
	LINKER_LANGUAGE CXX
	SOVERSION		${CMAKE_PROJECT_VERSION}
	VERSION 		${CMAKE_PROJECT_VERSION}
)

if (NOT WIN32)
	target_compile_options(StormByte PRIVATE -fPIC -fvisibility=hidden $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
endif()

if (STORMBYTE_AS_SUBPROJECT)
	target_include_directories(StormByte
		SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()

target_include_directories(StormByte
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	SYSTEM PUBLIC ${STORMBYTE_DIR}/include
)

# Enable features
target_include_directories(StormByte SYSTEM PRIVATE ${CMAKE_BINARY_DIR}/generated)
if (STORMBYTE_ENABLE_SQLITE)
	target_link_libraries(StormByte PUBLIC sqlite3)
endif()

# Install
install(TARGETS StormByte
	ARCHIVE 		DESTINATION "${CMAKE_INSTALL_LIBDIR}/StormByte"
	LIBRARY 		DESTINATION "${CMAKE_INSTALL_LIBDIR}/StormByte"
	RUNTIME 		DESTINATION ${CMAKE_INSTALL_BINDIR}
)
if (NOT WIN32)
	install(DIRECTORY ${STORMBYTE_DIR}/include/StormByte
		DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	)
	install(FILES ${CMAKE_BINARY_DIR}/generated/StormByte.h 			DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StormByte")
	install(FILES ${CMAKE_BINARY_DIR}/generated/StormByte/Features.h 	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StormByte")
	install(FILES ${STORMBYTE_CMAKE_DIR}/FindStormByte.cmake 			DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/Modules")
endif()