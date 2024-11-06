#include "StormByte/database/sqlite/exception.hxx"
#include "StormByte/database/sqlite/result.hxx"

using namespace StormByte::Database::SQLite;

Result::Result(const int& value):m_type(Type::Integer), m_value(value) {}

Result::Result(const std::string& value):m_type(Type::String), m_value(value) {}

Result::Result(std::string&& value):m_type(Type::String), m_value(std::move(value)) {}

Result::Result(std::nullptr_t):m_type(Type::Null), m_value() {}

bool Result::IsNull() const noexcept { return m_type == Type::Null; }

const Type& Result::GetType() const noexcept { return m_type; }

template<> const int& Result::Value<int>() const {
	if (m_type != Type::Integer)
		throw WrongResultType(m_type, Type::Integer);

	return std::get<int>(m_value);
}

template<> const bool& Result::Value<bool>() const {
	if (m_type != Type::Integer || std::get<int>(m_value) < 0 || std::get<int>(m_value) > 1)
		throw WrongResultType(m_type, Type::Bool);

	m_bool_conversion = std::get<int>(m_value) == 1;

	return m_bool_conversion;
}

template<> const std::string& Result::Value<std::string>() const {
	if (m_type != Type::String)
		throw WrongResultType(m_type, Type::String);

	return std::get<std::string>(m_value);
}
