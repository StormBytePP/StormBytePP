#include <StormByte/database/sqlite/exception.hxx>
#include <StormByte/database/sqlite/result/string.hxx>

using namespace StormByte::Database::SQLite;

String::String(const std::string& value):Result(Type::String), m_value(value) {}

String::String(std::string&& value):Result(Type::String), m_value(std::move(value)) {}

const int& String::AsInteger() const {
	throw WrongResultType(Type::String, Type::Integer);
}

bool String::AsBool() const {
	throw WrongResultType(Type::String, Type::Bool);
}

const std::string& String::AsString() const {
	return m_value;
}