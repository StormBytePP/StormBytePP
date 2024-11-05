#pragma once

#include <StormByte/config/parser.hxx>
#include <StormByte/config/item/group.hxx>

#include <filesystem>
#include <memory>
#include <string>

namespace StormByte::Config {
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
			void					ReadFromString(const std::string&);
			void 					Write();
			std::shared_ptr<Item>	LookUp(const std::string&) const;

		protected:
			virtual void			PostRead() noexcept = 0;

		private:
			void					Add(Item* parent, Parser::Content&& content);
			void					Add(Item* parent, std::vector<Parser::Content>&& content);
			std::unique_ptr<Group> m_root;
			std::filesystem::path m_file;
	};
}