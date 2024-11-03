file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/StormByte.h CONTENT "

#pragma once

#define STORMBYTE_VERSION \"${${PROJECT_NAME}_VERSION}\"

")