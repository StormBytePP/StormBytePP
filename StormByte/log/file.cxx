#include <StormByte/log/file.hxx>
#include <StormByte/system/exception.hxx>

#include <fstream>

using namespace StormByte::Log;

File::File(const Level& level, const std::filesystem::path& file):
Logger(level) {
	std::fstream* f = new std::fstream(file, std::ios::out | std::ios::app);
	if (!*f) {
		delete f;
		throw System::FileIOError(file, System::FileIOError::Write);
	}
	else
		m_out = f;
}

File::~File() noexcept {
	delete m_out;
	m_out = nullptr;
}