#include "StormByte++/config.hxx"
#include <libconfig.h++>

#ifdef LINUX
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#include <windows.h>
#include <tchar.h>
#define INFO_BUFFER_SIZE 32767
#endif

using namespace StormBytePP;

Config::Config(const std::filesystem::path& cfg_file):m_file(cfg_file) { SetOptions(); }

Config::Config(std::filesystem::path&& cfg_file):m_file(std::move(cfg_file)) { SetOptions(); }

void Config::Reload() {
	this->Initialize();
}

void Config::Write() {
	m_config.writeFile(m_file.string().c_str());
}

#ifdef WINDOWS
const std::string Config::ExpandEnvironmentVariable(const std::string& var) {
	return ExpandEnvironmentVariable(UTF8Decode(var));
}

const std::string Config::ExpandEnvironmentVariable(const std::wstring& var) {
	TCHAR  infoBuf[INFO_BUFFER_SIZE] = { '\0' };
	::ExpandEnvironmentStrings(var.c_str(), infoBuf, INFO_BUFFER_SIZE);

	return UTF8Encode(infoBuf);
}

std::string Config::UTF8Encode(const std::wstring& wstr) {
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

std::wstring Config::UTF8Decode(const std::string& str) {
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}
#endif

void Config::Initialize() {
	/* Clear contents */
	m_config.clear();

	try {
		m_config.readFile(m_file.string().c_str());
	}
	catch(...) {
		/* Ignored */
	}
}

const std::string Config::GetValueString(const libconfig::Setting& key) const {
	/* NOTES:
	* Windows does not transform automatically libconfig::Setting to std::string so
	* manually creating std::string with c_str is needed, this function is a wrapper
	* around it and will also expand Windows environment variables
	*/
	std::string result { key.c_str() };
	#ifdef WINDOWS
	if (!result.empty() && result[0] == '%' && result[result.length() - 1] == '%') {
		std::string expanded = ExpandEnvironmentVariable(result);
		result = expanded.empty() ? result : std::move(expanded);
	}
	#endif
	return result;
}

void Config::SetOptions() {
	m_config.setOptions(libconfig::Config::OptionFsync
    					| libconfig::Config::OptionSemicolonSeparators
    					| libconfig::Config::OptionColonAssignmentForGroups
    					| libconfig::Config::OptionOpenBraceOnSeparateLine);
}