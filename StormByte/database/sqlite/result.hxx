#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/database/sqlite/type.hxx>

	#include <string>

	namespace StormByte::Database::SQLite {
		class STORMBYTE_PUBLIC Result {
			public:
				Result(Type&&);
				Result(const Result&)							= default;
				Result(Result&&) noexcept						= default;
				Result& operator=(const Result&)				= default;
				Result& operator=(Result&&) noexcept			= default;
				~Result() noexcept								= default;

				virtual const int& 			AsInteger() const	= 0;
				virtual const std::string&	AsString() const	= 0;
				virtual bool 				AsBool() const 		= 0;
				virtual bool 				IsNull() const noexcept;

				const Type& 				GetType() const noexcept;

			protected:
				Type m_type;
		};
	}
#endif