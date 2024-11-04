#pragma once

#include <StormByte/visibility.h>

#include <stdexcept>
#include <string>

namespace StormByte {
	class STORMBYTE_PUBLIC Exception: public std::logic_error {
		public:
			Exception(const std::string&);
			Exception(const Exception&)					= default;
			Exception& operator=(const Exception&)		= default;
			virtual ~Exception() noexcept				= default;
	};
}