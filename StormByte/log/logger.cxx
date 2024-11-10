#include <StormByte/log/logger.hxx>

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace StormByte::Log;

const Logger Logger::endl { Level::Debug }; // Level will just be ignored

Logger::Logger(const Level& level) noexcept:m_print_level(level),
m_current_level(level), m_out(nullptr) {}

Logger& Logger::operator<<(const Level& level) noexcept {
	m_current_level = level;
	if (m_out && m_current_level >= m_print_level)
		print_header();
	return *this;
}

Logger& Logger::operator<<(const std::string& str) noexcept {
	if (m_out && m_current_level >= m_print_level)
		*m_out << str;
	return *this;
}

Logger& Logger::operator<<(const Logger&) noexcept {
	if (m_out && m_current_level >= m_print_level)
		*m_out << std::endl;
	return *this;
}

void Logger::print_time() const noexcept {
	auto rawtime = std::time(nullptr);
    struct tm timeinfo;
	#ifdef LINUX
	timeinfo = *std::localtime(&rawtime);
	#else
	// Windows warns about CRT_INSECURE_BLABLABLA
	localtime_s(&timeinfo, &rawtime);
	#endif
	*m_out << std::put_time(&timeinfo, "%d/%m/%Y %H:%M:%S");
}

void Logger::print_level() const noexcept {
	switch(m_current_level) {
		case Level::Debug:
			*m_out << "[DEBUG  ]";
			break;

		case Level::Warning:
			*m_out << "[WARNING]";
			break;

		case Level::Notice:
			*m_out << "[NOTICE ]";
			break;

		case Level::Info:
			*m_out << "[INFO   ]";
			break;

		case Level::Error:
			*m_out << "[ERROR  ]";
			break;

		case Level::Fatal:
			*m_out << "[FATAL  ]";
			break;
	}
}

void Logger::print_header() const noexcept {
	print_time();
	*m_out << " ";
	print_level();
	*m_out << ": ";
}