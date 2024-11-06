#include <StormByte/system/exception.hxx>

#include <cstring>

using namespace StormByte::System;

Exception::Exception(const std::string& message):m_data(message) {}

const char* Exception::what() const noexcept {
	return m_data.c_str();
}
