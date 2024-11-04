#pragma once

#include <StormByte/visibility.h>

#include <string>

namespace StormByte::System {
	class STORMBYTE_PUBLIC Exception {
		public:
			Exception(const std::string&);
			Exception(const Exception&);
			Exception(Exception&) noexcept;;
			Exception& operator=(const Exception&);
			Exception& operator=(Exception&&) noexcept;
			virtual ~Exception() noexcept;
			virtual const char* what() const noexcept;

		private:
			char* m_data;

			void copy(const char*);
			void copy(const std::string&);
			void free();
	};
}