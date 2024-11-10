#pragma once

#include <StormByte/system/definitions.h>

#include <filesystem>
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

	class STORMBYTE_PUBLIC FileIOError final: public Exception {
		public:
			enum Operation { Read = 0, Write }; 
			FileIOError(const std::filesystem::path&, const Operation&);
			FileIOError(const FileIOError&)				= default;
			FileIOError& operator=(const FileIOError&)	= default;
			~FileIOError() noexcept override			= default;

		private:
			std::string operation_to_string(const Operation&) const noexcept;
	};
}