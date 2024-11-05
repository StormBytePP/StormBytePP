#include <StormByte/database/sqlite/exception.hxx>
#include <StormByte/database/sqlite/result/integer.hxx>

using namespace StormByte::Database::SQLite;

Integer::Integer(const int& value):Result(Type::Integer), m_value(value) {}

const int& Integer::AsInteger() const { return m_value; }

const std::string& Integer::AsString() const {
	throw WrongResultType(Type::Integer, Type::String);
}

bool Integer::AsBool() const { return m_value == 1; }