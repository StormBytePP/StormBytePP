#include <StormByte/config/exception.hxx>

using namespace StormByte::Config;

Exception::Exception(const std::string& msg):System::Exception(msg) {}

WrongValueTypeConversion::WrongValueTypeConversion(const Item& item, const std::string& method):
Exception(method + " conversion failed for " + item.GetName() + "(" + item.GetTypeAsString() + ")") {}

ValueFailure::ValueFailure(const Item& item, const Item::Type& type):
Exception("Try to add/set " + Item::GetTypeAsString(type) + " value to " + item.GetName() + " which is of type " + item.GetTypeAsString()) {}

InvalidName::InvalidName(const std::string& name):
Exception("Invalid name " + name + " given as identifier, only alfanumeric is allowed") {}

FileIOError::FileIOError(const std::string& file, const std::string& operation):
Exception("File " + file + " can not be opened for " + operation) {}

ParseError::ParseError(const std::string& fragment):
Exception("Parse error near " + fragment) {}

ParseError::ParseError(const std::string& name, const std::string& fragment):
Exception("Parse error on " + name + " near " + fragment) {}

ParseError::ParseError(const std::string& name, const std::string& fragment, const std::string& reason):
Exception("Parse error (" + reason + ") on " + name + " near " + fragment) {}

ItemNotFound::ItemNotFound(const std::string& name):
Exception("Item " + name + " do not exist") {}