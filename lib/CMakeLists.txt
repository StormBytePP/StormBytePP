include(GNUInstallDirs)
set(STORMBYTE_HEADERS
	${STORMBYTE_DIR}/include/StormByte/config/exception.hxx
	${STORMBYTE_DIR}/include/StormByte/config/file.hxx
	${STORMBYTE_DIR}/include/StormByte/config/item.hxx
	${STORMBYTE_DIR}/include/StormByte/config/parser.hxx
	${STORMBYTE_DIR}/include/StormByte/config/item/group.hxx
	${STORMBYTE_DIR}/include/StormByte/config/item/value.hxx
	${STORMBYTE_DIR}/include/StormByte/config/item/value/integer.hxx
	${STORMBYTE_DIR}/include/StormByte/config/item/value/string.hxx
	${STORMBYTE_DIR}/include/StormByte/system/exception.hxx
	${STORMBYTE_DIR}/include/StormByte/system/executable.hxx
	${STORMBYTE_DIR}/include/StormByte/system/pipe.hxx
	${STORMBYTE_DIR}/include/StormByte/system/worker.hxx
	${STORMBYTE_DIR}/include/StormByte/visibility.h
)
set(STORMBYTE_SOURCES
	${STORMBYTE_DIR}/lib/config/exception.cxx
	${STORMBYTE_DIR}/lib/config/file.cxx
	${STORMBYTE_DIR}/lib/config/item.cxx
	${STORMBYTE_DIR}/lib/config/parser.cxx
	${STORMBYTE_DIR}/lib/config/item/group.cxx
	${STORMBYTE_DIR}/lib/config/item/value.cxx
	${STORMBYTE_DIR}/lib/config/item/value/integer.cxx
	${STORMBYTE_DIR}/lib/config/item/value/string.cxx
	${STORMBYTE_DIR}/lib/system/exception.cxx
	${STORMBYTE_DIR}/lib/system/executable.cxx
	${STORMBYTE_DIR}/lib/system/pipe.cxx
	${STORMBYTE_DIR}/lib/system/worker.cxx
)

# SQLite support
if(STORMBYTE_ENABLE_SQLITE)
	list(APPEND STORMBYTE_SOURCES
		${STORMBYTE_DIR}/lib/sqlite3.cxx
	)
endif()

if (NOT STORMBYTE_AS_SUBPROJECT OR WIN32)
	add_library(StormByte SHARED ${STORMBYTE_SOURCES})
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
	target_compile_options(StormByte PRIVATE -fPIC)
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