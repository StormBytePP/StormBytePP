#include <StormByte/system/exception.hxx>

#include <cstring>

using namespace StormByte::System;

Exception::Exception(const std::string& message):m_data(message) {}

const char* Exception::what() const noexcept {
	return m_data.c_str();
}

FileIOError::FileIOError(const std::filesystem::path& file, const Operation& operation):
Exception("File " + file.string() + " can not be opened for " + operation_to_string(operation)) {}

std::string FileIOError::operation_to_string(const Operation& op) const noexcept {
	std::string out = "";
	switch(op) {
		case Operation::Read:
			out = "read";
			break;

		case Operation::Write:
			out = "write";
			break;
	};
	return out;
}