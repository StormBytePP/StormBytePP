#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/database/sqlite/type.hxx>

	#include <cstdint>
	#include <string>
	#include <variant>

	namespace StormByte::Database::SQLite {
		class STORMBYTE_PUBLIC Result {
			public:
				Result(const int64_t&);
				Result(const std::string&);
				Result(std::string&&);
				Result(std::nullptr_t);
				Result(const Result&)							= default;
				Result(Result&&) noexcept						= default;
				Result& operator=(const Result&)				= default;
				Result& operator=(Result&&) noexcept			= default;
				~Result() noexcept								= default;

				virtual bool 							IsNull() const noexcept;
				template<typename T> const T&			Value() const;

				const Type& 							GetType() const noexcept;

			protected:
				Type m_type;
				std::variant<int64_t, std::string> m_value;
				mutable bool m_bool_conversion;
				mutable int m_int_conversion;
		};
	}
#endif