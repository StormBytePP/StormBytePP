if (WITH_SYSTEM_CONFIG++)
	find_package (Config++ REQUIRED)
else()
    FILE(GLOB_RECURSE libsrc_cpp "src/lib/*.c" "src/lib/*.cc")

	if (WIN32)
    	add_library(config++ SHARED ${libsrc_cpp})
		install(TARGETS config++
			ARCHIVE 		DESTINATION ${CMAKE_INSTALL_LIBDIR}
			LIBRARY 		DESTINATION ${CMAKE_INSTALL_LIBDIR}
			RUNTIME 		DESTINATION ${CMAKE_INSTALL_BINDIR}
		)
	else()
		add_library(config++ STATIC ${libsrc_cpp})
		target_compile_options(config++ PRIVATE -fPIC -fvisibility=hidden $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
	endif()

    target_include_directories(config++
		SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
	)
    target_compile_definitions(config++ PRIVATE LIBCONFIGXX_EXPORTS)
    
    include(CheckSymbolExists)
    check_symbol_exists(uselocale "locale.h" HAVE_USELOCALE)
    check_symbol_exists(newlocale "locale.h" HAVE_NEWLOCALE)
    check_symbol_exists(freelocale "locale.h" HAVE_FREELOCALE)

    if(HAVE_USELOCALE)
        target_compile_definitions(config++
            PRIVATE "HAVE_USELOCALE")
    endif()

    if(HAVE_NEWLOCALE)
        target_compile_definitions(config++
            PRIVATE "HAVE_NEWLOCALE")
    endif()

    if(HAVE_FREELOCALE)
        target_compile_definitions(config++
            PRIVATE "HAVE_FREELOCALE")
    endif()

    if(MSVC)
        target_compile_definitions(config++
            PRIVATE
                _CRT_SECURE_NO_DEPRECATE
                YY_NO_UNISTD_H
                YY_USE_CONST )
    endif()

    if(WIN32)
        target_link_libraries(config++ shlwapi)
    endif()

endif()
