if (WITH_SYSTEM_CONFIG++)
	find_package (Config++ REQUIRED)
else()
	set(LIBCONFIG_DIR ${CMAKE_CURRENT_LIST_DIR}/src/lib)
	set(libconfigsrc
			${LIBCONFIG_DIR}/grammar.c
			${LIBCONFIG_DIR}/libconfig.c
			${LIBCONFIG_DIR}/scanctx.c
			${LIBCONFIG_DIR}/scanner.c
			${LIBCONFIG_DIR}/strbuf.c
			${LIBCONFIG_DIR}/strvec.c
			${LIBCONFIG_DIR}/util.c
			${LIBCONFIG_DIR}/wincompat.c
	)
	set(libconfigppsrc
			${LIBCONFIG_DIR}/libconfigcpp.cc
	)

	add_library(config STATIC ${libconfigsrc})

	include(CheckSymbolExists)
    check_symbol_exists(uselocale "locale.h" HAVE_USELOCALE)
    check_symbol_exists(newlocale "locale.h" HAVE_NEWLOCALE)
    check_symbol_exists(freelocale "locale.h" HAVE_FREELOCALE)

    if(HAVE_USELOCALE)
        target_compile_definitions(config
            PRIVATE "HAVE_USELOCALE")
    endif()

    if(HAVE_NEWLOCALE)
        target_compile_definitions(config
            PRIVATE "HAVE_NEWLOCALE")
    endif()

    if(HAVE_FREELOCALE)
        target_compile_definitions(config
            PRIVATE "HAVE_FREELOCALE")
    endif()

	if (WIN32)
    	add_library(config++ SHARED ${libconfigppsrc})
		install(TARGETS config++
			ARCHIVE 		DESTINATION ${CMAKE_INSTALL_LIBDIR}
			LIBRARY 		DESTINATION ${CMAKE_INSTALL_LIBDIR}
			RUNTIME 		DESTINATION ${CMAKE_INSTALL_BINDIR}
		)
	else()
		add_library(config++ STATIC ${libconfigppsrc})
		target_compile_options(config PRIVATE -fPIC -fvisibility=hidden $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
		target_compile_options(config++ PRIVATE -fPIC -fvisibility=hidden $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
	endif()
	target_link_libraries(config++ PRIVATE config)

    target_include_directories(config++
		SYSTEM INTERFACE ${LIBCONFIG_DIR}
	)
    target_compile_definitions(config++ PRIVATE LIBCONFIGXX_EXPORTS)

    if(MSVC)
	target_compile_definitions(config
		PRIVATE
			_CRT_SECURE_NO_DEPRECATE
			YY_NO_UNISTD_H
			YY_USE_CONST
	)

	target_compile_definitions(config++
		PRIVATE
			_CRT_SECURE_NO_DEPRECATE
			YY_NO_UNISTD_H
			YY_USE_CONST
	)
    endif()

    if(WIN32)
        target_link_libraries(config++ PRIVATE shlwapi)
    endif()

endif()
