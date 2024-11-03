
#include <StormByte/sqlite3.hxx>

using namespace StormByte;

SQLite3::SQLite3(const std::filesystem::path& dbfile):m_database_file(dbfile) {}

SQLite3::SQLite3(std::filesystem::path&& dbfile):m_database_file(std::move(dbfile)) {}

SQLite3::~SQLite3() { close_database(); }

SQLite3::Exception::Exception(const std::string& message):std::runtime_error(message) {}

SQLite3::Exception::Exception(std::string&& message):std::runtime_error(std::move(message)) {}

void SQLite3::init_database() {
	close_database(); // In case it was called more than once and if so we reset connection
	int rc = sqlite3_open(m_database_file.string().c_str(), &m_database); // Windows needs this string intermediate conversion

	if (rc != SQLITE_OK) {
		const std::string message = "Cannot open database " + m_database_file.string() + ": " + std::string(sqlite3_errmsg(m_database)); // SQLite3 handles internally freeing message's memory
		close_database(); // Need to close database here as exception throwing will skip destructor
        throw std::runtime_error(message);
    }
	enable_foreign_keys();
	prepare_sentences();
}

void SQLite3::close_database() {
	if (m_database) {
		for (auto it = m_prepared.begin(); it != m_prepared.end(); it++)
			sqlite3_finalize(it->second);
		m_prepared.clear();
		sqlite3_close(m_database);
		m_database = nullptr;
	}
}

void SQLite3::enable_foreign_keys() {
	sqlite3_exec(m_database, "PRAGMA foreign_keys = OFF", nullptr, nullptr, nullptr);
}

void SQLite3::throw_error(std::string&& err_msg) {
	throw Exception(std::move(err_msg));
}

void SQLite3::reset_stmt(sqlite3_stmt* stmt) {
	sqlite3_clear_bindings(stmt);
	sqlite3_reset(stmt);
}

void SQLite3::begin_transaction() {
	sqlite3_exec(m_database, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
}

void SQLite3::begin_exclusive_transaction() {
	sqlite3_exec(m_database, "BEGIN EXCLUSIVE TRANSACTION;", nullptr, nullptr, nullptr);
}

void SQLite3::commit_transaction() {
	sqlite3_exec(m_database, "COMMIT;", nullptr, nullptr, nullptr);
}

void SQLite3::rollback_transaction() {
	sqlite3_exec(m_database, "ROLLBACK;", nullptr, nullptr, nullptr);
}

void SQLite3::prepare_sentences() {
	std::map<std::string, std::string> all_prepared_stmts = this->all_prepared_statements(); // For polymorphism
	for (auto it = all_prepared_stmts.begin(); it != all_prepared_stmts.end(); it++) {
		std::pair<std::string, sqlite3_stmt*> statement = { std::move(it->first), nullptr };
		sqlite3_prepare_v2( m_database, it->second.c_str(), static_cast<int>(it->second.length()), &statement.second, nullptr);
		if (!statement.second)
			throw_error("Prepared sentence " + statement.first + " can not be loaded!");
		else
			m_prepared.insert(std::move(statement));
	}
}
