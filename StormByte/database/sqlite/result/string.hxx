#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/database/sqlite/result.hxx>

	namespace StormByte::Database::SQLite {
		class STORMBYTE_PUBLIC String final: public Result {
			public:
				String(const std::string&);
				String(std::string&&);
				String(const String&)							= default;
				String(String&&) noexcept						= default;
				String& operator=(const String&)				= default;
				String& operator=(String&&) noexcept			= default;
				~String() noexcept								= default;

				const int& 			AsInteger() const override;
				bool 				AsBool() const override;
				const std::string&	AsString() const override;

			private:
				std::string m_value;
		};
	}
#endif