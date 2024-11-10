#pragma once

#include <StormByte/log/logger.hxx>

#include <filesystem>

namespace StormByte::Log {
	class STORMBYTE_PUBLIC File final: public Logger {
		public:
			File(const Level&, const std::filesystem::path&);
			File(const File&&)					= delete;
			File(File&) noexcept				= default;
			File& operator=(const File&)		= delete;
			File& operator=(File&&) noexcept	= default;
			~File() noexcept override;
	};
}