#pragma once

#include <StormByte/visibility.h>

#include <string>

namespace StormByte::System {
	class STORMBYTE_PUBLIC Exception {
		public:
			Exception(const std::string&);
			Exception(const Exception&)					= default;
			Exception(Exception&&) noexcept				= default;
			Exception& operator=(const Exception&)		= default;
			Exception& operator=(Exception&&) noexcept	= default;
			virtual ~Exception() noexcept				= default;
			
			virtual const char* what() const noexcept;

		private:
			std::string m_data;
	};
}