#include <StormByte/config/exception.hxx>

using namespace StormByte::Config;

WrongValueTypeConversion::WrongValueTypeConversion(const Item& item, const std::string& method):
Exception(method + " conversion failed for " + item.GetName() + "(" + item.GetTypeAsString() + ")") {}

ValueFailure::ValueFailure(const Item& item, const Item::Type& type):
Exception("Try to add/set " + Item::GetTypeAsString(type) + " value to " + item.GetName() + " which is of type " + item.GetTypeAsString()) {}

FileIOError::FileIOError(const std::string& file, const std::string& operation):
Exception("File " + file + " can not be opened for " + operation) {}