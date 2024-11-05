#include <StormByte/database/sqlite/exception.hxx>

using namespace StormByte::Database::SQLite;

Exception::Exception(const std::string& msg):System::Exception(msg) {}

Exception::Exception(std::string&& msg) noexcept:System::Exception(std::move(msg)) {}

WrongResultType::WrongResultType(const Type& source_type, const Type& asked_type):
Exception("Wrong value type: Requested " + std::move(type_to_string(asked_type)
	+ " whereas contained type is " + std::move(type_to_string(source_type)))) {}

std::string WrongResultType::type_to_string(const Type& type) const {
	std::string t = "";
	switch (type) {
		case Type::Integer:
			t = "integer";
			break;

		case Type::Bool:
			t = "bool";
			break;

		case Type::Null:
			t = "NULL";
			break;

		case Type::String:
			t = "string";
			break;
	}
	return t;
}

OutOfBounds::OutOfBounds(const size_t& max, const size_t& asked):
Exception("Out of bounds: Asked for column number " +
std::to_string(asked) + " when there is only " + std::to_string(max)) {}

OutOfBounds::OutOfBounds(const std::string& name):
Exception("Out of bounds: Column name " + name + " do not exist") {}

ConnectionError::ConnectionError(const std::string& reason):
Exception(reason) {}

ConnectionError::ConnectionError(std::string&& reason):
Exception(std::move(reason)) {}

QueryError::QueryError(const std::string& reason):
Exception(reason) {}

QueryError::QueryError(std::string&& reason):
Exception(std::move(reason)) {}
