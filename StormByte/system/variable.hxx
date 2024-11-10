#pragma once

#include <StormByte/visibility.h>

#include <string>

namespace StormByte::System {
	struct STORMBYTE_PUBLIC Variable {
		public:
			static std::string 		Expand(const std::string&);
			#ifdef WINDOWS
			static std::string 		Expand(const std::wstring&);
			#endif

		private:
			static std::string		ExpandEnvironmentVariable(const std::string&);
			#ifdef WINDOWS
			static std::string		ExpandEnvironmentVariable(const std::wstring&);
			static std::string		UTF8Encode(const std::wstring&);
			static std::wstring		UTF8Decode(const std::string&);
			#else
			static std::string		HomePath();
			#endif
	};
}