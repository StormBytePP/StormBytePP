#include "StormByte/config/item/value.hxx"
#include "StormByte/config/exception.hxx"

using namespace StormByte::Config;

Value::Value(const Type& type, const std::string& name):
Item(type, name) {}

Value::Value(const Type& type, std::string&& name):
Item(type, name) {}

Group& Value::AsGroup() {
	throw WrongValueTypeConversion(*this, "AsGroup");
}

std::shared_ptr<Item> Value::Add(const std::string&, const Type& t) {
	throw WrongValueTypeConversion(*this, GetTypeAsString(t));
}