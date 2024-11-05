#include <StormByte/database/sqlite/exception.hxx>
#include <StormByte/database/sqlite/result.hxx>

using namespace StormByte::Database::SQLite;

Result::Result(Type&& type):m_type(std::move(type)) {}

bool Result::IsNull() const noexcept { return false; }

const Type& Result::GetType() const noexcept { return m_type; }