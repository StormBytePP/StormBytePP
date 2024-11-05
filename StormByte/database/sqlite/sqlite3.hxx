#pragma once

#ifdef STORMBYTE_ENABLE_SQLITE
	#include <StormByte/visibility.h>

	#include <filesystem>
	#include <list>
	#include <map>
	#include <memory>

	class sqlite3;
	namespace StormByte::Database::SQLite {
		class PreparedSTMT;
		class Row;
		class STORMBYTE_PUBLIC SQLite3 {
			public:
				SQLite3(const SQLite3& db) 					= delete;
				SQLite3(SQLite3&& db) noexcept				= default;
				SQLite3& operator=(const SQLite3& db) 		= delete;
				SQLite3& operator=(SQLite3&& db) noexcept 	= default;
				virtual ~SQLite3();

			protected:
				SQLite3(const std::filesystem::path& dbfile);
				SQLite3(std::filesystem::path&& dbfile);

				void 							init_database();
				inline void 					begin_transaction();
				inline void 					begin_exclusive_transaction();
				inline void 					commit_transaction();
				inline void 					rollback_transaction();
				std::shared_ptr<PreparedSTMT>	get_prepared(const std::string&);
				void							silent_query(const std::string&);
				const std::string				last_error();

				virtual const std::map<std::string, std::string>& all_prepared_statements() const = 0;
				std::map<std::string, std::shared_ptr<PreparedSTMT>> m_prepared;

			private:
				std::filesystem::path m_database_file;
				sqlite3* m_database;

				/* Database internals */
				virtual void post_init_action();
				void close_database();
				void enable_foreign_keys();
				void prepare_sentences();
		};
	}
 #endif