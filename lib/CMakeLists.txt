include(GNUInstallDirs)
set(STORMBYTE_HEADERS
	${STORMBYTE_DIR}/lib/StormByte/config.hxx
	${STORMBYTE_DIR}/lib/StormByte/visibility.h
)
set(STORMBYTE_SOURCES
	${STORMBYTE_DIR}/lib/StormByte/config.cxx
	#${STORMBYTE_DIR}/lib/StormByte/sqlite3.cxx
)

if (NOT STORMBYTE_AS_SUBPROJECT OR WIN32)
	add_library(StormByte SHARED ${STORMBYTE_SOURCES} ${STORMBYTE_HEADERS})
	install(TARGETS StormByte
		ARCHIVE 		DESTINATION "${CMAKE_INSTALL_LIBDIR}/StormByte"
		LIBRARY 		DESTINATION "${CMAKE_INSTALL_LIBDIR}/StormByte"
		RUNTIME 		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
	install(FILES ${STORMBYTE_HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StormByte")
	install(FILES ${CMAKE_BINARY_DIR}/generated/StormByte.h DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StormByte")
else()
	add_library(StormByte STATIC ${STORMBYTE_SOURCES})
endif()
target_compile_definitions(StormByte PRIVATE BUILDING_STORMBYTE)
set_target_properties(StormByte PROPERTIES
	LINKER_LANGUAGE CXX
	SOVERSION		${CMAKE_PROJECT_VERSION}
	VERSION 		${CMAKE_PROJECT_VERSION}
)
target_link_libraries(StormByte PUBLIC config++)
if (NOT WIN32)
	target_compile_options(StormByte PRIVATE -fPIC -fvisibility=hidden $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
endif()

if (STORMBYTE_AS_SUBPROJECT)
	target_include_directories(StormByte
		SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()
target_link_libraries(StormByte
	PUBLIC sqlite3
	PUBLIC config++
)
target_include_directories(StormByte PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})