file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/version.h CONTENT "

#pragma once

#define STORMBYTEPP_VERSION			\"${${PROJECT_NAME}_VERSION}\"

")