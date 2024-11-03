#include <StormByte/exception.hxx>

using namespace StormByte;

Exception::Exception(const std::string& message):std::logic_error(message) {}