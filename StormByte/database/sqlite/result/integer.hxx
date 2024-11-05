#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/database/sqlite/result.hxx>

	namespace StormByte::Database::SQLite {
		class STORMBYTE_PUBLIC Integer final: public Result {
			public:
				Integer(const int&);
				Integer(const Integer&)							= default;
				Integer(Integer&&) noexcept						= default;
				Integer& operator=(const Integer&)				= default;
				Integer& operator=(Integer&&) noexcept			= default;
				~Integer() noexcept								= default;

				const int& 			AsInteger() const override;
				const std::string&	AsString() const override;
				bool 				AsBool() const override;

			private:
				int m_value;
		};
	}
#endif