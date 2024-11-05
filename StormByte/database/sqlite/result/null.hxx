#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/database/sqlite/result.hxx>

	namespace StormByte::Database::SQLite {
		class STORMBYTE_PUBLIC Null final: public Result {
			public:
				Null();
				Null(const Null&)							= default;
				Null(Null&&) noexcept						= default;
				Null& operator=(const Null&)				= default;
				Null& operator=(Null&&) noexcept			= default;
				~Null() noexcept							= default;

				const int& 			AsInteger() const override;
				const std::string&	AsString() const override;
				bool 				AsBool() const override;
				bool 				IsNull() const noexcept override;
		};
	}
#endif