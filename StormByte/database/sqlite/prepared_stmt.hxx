#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/database/sqlite/result/row.hxx>

	#include <memory>
	#include <optional>
	#include <string>

	class sqlite3_stmt;
	namespace StormByte::Database::SQLite {
		class STORMBYTE_PUBLIC PreparedSTMT {
			friend class SQLite3;
			public:
				PreparedSTMT(const PreparedSTMT&) 					= delete;
				PreparedSTMT(PreparedSTMT&&) noexcept				= default;
				PreparedSTMT& operator=(const PreparedSTMT&)		= delete;
				PreparedSTMT& operator=(PreparedSTMT&&) noexcept	= default;
				~PreparedSTMT() noexcept;

				void 					Bind(const int&, const int&) noexcept;
				void 					Bind(const int&, const std::string&) noexcept;
				inline void 			Bind(const int&, bool) noexcept;
				void 					Bind(const int&, const void*) noexcept; // Sintactic sugar for bind NULL
				void 					Bind(const int&, const std::optional<int>&) noexcept;
				void 					Bind(const int&, const std::optional<std::string>&) noexcept;
				inline void				Bind(const int&, const std::optional<bool>&) noexcept;

				void 					Reset() noexcept;
				std::shared_ptr<Row> 	Step();

			private:
				PreparedSTMT(const std::string&);
				PreparedSTMT(std::string&&) noexcept;

				std::string m_query;
				sqlite3_stmt* m_stmt;
		};
	}
#endif