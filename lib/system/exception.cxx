#include <StormByte/system/exception.hxx>

#include <cstring>

using namespace StormByte::System;

Exception::Exception(const std::string& message):m_data(nullptr) {
	copy(message);
}

const char* Exception::what() const noexcept {
	return m_data;
}

void Exception::copy(const char* message) {
	free();
	std::memcpy(m_data, message, std::strlen(message));
}

void Exception::copy(const std::string& message) {
	copy(message.c_str());
}

void Exception::free() {
	if (m_data) {
		std::free(m_data);
		m_data = nullptr;
	}
}