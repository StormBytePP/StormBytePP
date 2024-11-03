#pragma once

#include <StormByte/visibility.h>

#include <filesystem>
#include <memory>
#include <string>

namespace StormByte::Config {
	class Group;
	class STORMBYTE_PUBLIC File {
		public:
			File(const std::filesystem::path&);
			File(std::filesystem::path&&);
			File(const File&);
			File(File&&) noexcept				= default;
			File& operator=(const File&);
			File& operator=(File&&) noexcept	= default;
			virtual ~File()						= default;

			std::shared_ptr<Item>	Add(const std::string&, const Item::Type&);
			void 					Clear() noexcept;
			void 					Read();
			void 					Write();

		private:
			std::unique_ptr<Group> m_root;
			std::filesystem::path m_file;
	};
}