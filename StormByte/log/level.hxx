#pragma once

#include <StormByte/system/definitions.h>

namespace StormByte::Log {
	enum class STORMBYTE_PUBLIC Level {
		Debug = 0,
		Warning,
		Notice,
		Info,
		Error,
		Fatal
	};
}