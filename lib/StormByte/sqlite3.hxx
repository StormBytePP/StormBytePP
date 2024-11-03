#pragma once

#include <StormByte/visibility.h>

#include <filesystem>
#include <list>
#include <map>
#include <sqlite3.h>

namespace StormByte {
	class STORMBYTE_PUBLIC SQLite3 {
		public:
			SQLite3(const std::filesystem::path& dbfile);
			SQLite3(std::filesystem::path&& dbfile);
			SQLite3(const SQLite3& db) 					= delete;
			SQLite3(SQLite3&& db) noexcept				= default;
			SQLite3& operator=(const SQLite3& db) 		= delete;
			SQLite3& operator=(SQLite3&& db) noexcept 	= default;
			virtual ~SQLite3();

			class STORMBYTE_PUBLIC Exception: public std::runtime_error {
				public:
					Exception(const std::string&);
					Exception(std::string&&);
					Exception(const Exception&)					= default;
					Exception(Exception&&) noexcept				= default;
					Exception& operator=(const Exception&)		= default;
					Exception& operator=(Exception&&) noexcept	= default;
					~Exception()								= default;
			};

		protected:
			void reset_stmt(sqlite3_stmt*);
			inline void begin_transaction();
			inline void begin_exclusive_transaction();
			inline void commit_transaction();
			inline void rollback_transaction();
			virtual std::map<std::string, std::string> all_prepared_statements() const = 0;

		private:
			std::filesystem::path m_database_file;
			sqlite3* m_database;
			std::map<std::string, sqlite3_stmt*> m_prepared;

			/* Database internals */
			void init_database();
			void close_database();
			void enable_foreign_keys();
			void prepare_sentences();
			void throw_error(std::string&&);
	};
}