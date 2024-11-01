include(GNUInstallDirs)
set(STORMBYTE_HEADERS
	${STORMBYTE_DIR}/lib/StormByte/config.hxx
	${STORMBYTE_DIR}/lib/StormByte/visibility.h
)
set(STORMBYTE_SOURCES
	${STORMBYTE_DIR}/lib/StormByte/config.cxx
)

if (NOT STORMBYTE_AS_SUBPROJECT OR WIN32)
	add_library(StormByte++ SHARED ${STORMBYTE_SOURCES} ${STORMBYTE_HEADERS})
	install(TARGETS StormByte++
		ARCHIVE 		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY 		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME 		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
	install(FILES ${STORMBYTE_HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StormByte")
else()
	add_library(StormByte++ STATIC ${STORMBYTE_SOURCES})
endif()
set_target_properties(StormByte++ PROPERTIES
	LINKER_LANGUAGE CXX
	SOVERSION		${CMAKE_PROJECT_VERSION}
	VERSION 		${CMAKE_PROJECT_VERSION}
)
target_link_libraries(StormByte++ PUBLIC config++)
target_compile_options(StormByte++ PRIVATE -fPIC)

if (STORMBYTE_AS_SUBPROJECT)
	target_include_directories(StormByte++
		SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()