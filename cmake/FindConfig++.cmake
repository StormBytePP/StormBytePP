# Look for the necessary header
find_path(Config++_INCLUDE_DIR NAMES libconfig.h++)
mark_as_advanced(Config++_INCLUDE_DIR)

# Look for the necessary library
find_library(Config++_LIBRARY NAMES config++ config++)
mark_as_advanced(Config++_LIBRARY)

# Create the imported target
if(Config++_LIBRARY AND Config++_INCLUDE_DIR)
    if(NOT TARGET Config++)
        add_library(Config++ UNKNOWN IMPORTED)
        set_target_properties(Config++ PROPERTIES
            IMPORTED_LOCATION             "${Config++_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${Config++_INCLUDE_DIR}"
		)
    endif()
	message(STATUS "Found Config++: ${Config++_LIBRARY}")
else()
	message(FATAL_ERROR "Could NOT find Config++ library")
endif()
