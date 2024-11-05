#include <StormByte/database/sqlite/exception.hxx>
#include <StormByte/database/sqlite/result/null.hxx>

using namespace StormByte::Database::SQLite;

Null::Null():Result(Type::Null) {}

const int& Null::AsInteger() const {
	throw WrongResultType(Type::Null, Type::Integer);
}

bool Null::AsBool() const {
	throw WrongResultType(Type::Null, Type::Bool);
}

const std::string& Null::AsString() const {
	throw WrongResultType(Type::Null, Type::String);
}

bool Null::IsNull() const noexcept { return true; }