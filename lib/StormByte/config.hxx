#pragma once

#include "visibility.h"

#include <filesystem>
#include <libconfig.h++>
#include <map>
#include <memory>

namespace StormByte {
	class DLL_PUBLIC Config {
		public:
			virtual ~Config()										= default;
			
			void													Reload();
			void 													Write();

		protected:
			virtual void											Initialize() = 0;
			const std::string										GetValueString(const libconfig::Setting&) const;

		private:
			Config(const std::filesystem::path&);
			Config(std::filesystem::path&&);
			Config(const Config&)									= delete;
			Config(Config&&)										= delete;
			Config& operator=(const Config&)						= delete;
			Config& operator=(Config&&)								= delete;

			#ifdef WINDOWS
			static const std::string								ExpandEnvironmentVariable(const std::string&);
			static const std::string								ExpandEnvironmentVariable(const std::wstring&);
			static std::string										UTF8Encode(const std::wstring&);
			static std::wstring										UTF8Decode(const std::string&);
			#endif

			libconfig::Config										m_config;
			std::filesystem::path									m_file;
	};
}