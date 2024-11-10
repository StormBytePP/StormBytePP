#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/system/definitions.h>

	namespace StormByte::Database::SQLite {
		enum class STORMBYTE_PUBLIC Type: unsigned short {
			Integer = 0,
			Bool,
			String,
			Null
		};
	}
#endif