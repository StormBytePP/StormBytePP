#pragma once

#include <StormByte/log/level.hxx>

#include <ostream>

namespace StormByte::Log {
	class STORMBYTE_PUBLIC Logger {
		public:
			Logger(const Logger&)					= delete;
			Logger(Logger&&) noexcept				= default;
			Logger& operator=(const Logger&)		= delete;
			Logger& operator=(Logger&&) noexcept	= default;
			virtual ~Logger() noexcept				= default;

			Logger& operator<<(const Level&) noexcept;
			Logger& operator<<(const std::string&) noexcept;
			Logger& operator<<(const Logger&) noexcept;

			static const Logger endl;

		protected:
			Logger(const Level&) noexcept;
			void print_time() const noexcept;
			void print_level() const noexcept;
			void print_header() const noexcept;

			Level m_print_level, m_current_level;
			std::ostream* m_out;
	};
}