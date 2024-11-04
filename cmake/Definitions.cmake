file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/StormByte.h CONTENT "#pragma once

#define STORMBYTE_VERSION \"${${PROJECT_NAME}_VERSION}\"")

file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/StormByte/Features.h CONTENT "#pragma once

#define STORMBYTE_SQLITE ${STORMBYTE_ENABLE_SQLITE}")