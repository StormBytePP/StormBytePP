#pragma once

#include <StormByte/config/item.hxx>

#include <fstream>
#include <sstream>
#include <vector>

namespace StormByte::Config {
	class STORMBYTE_PRIVATE Parser {
		public:
			struct STORMBYTE_PRIVATE Content {
				std::string s_name;
				Item::Type s_type;
				std::string s_content;
			};

			Parser(std::ifstream&&);
			Parser(std::istringstream&&);
			Parser(const Parser&) 					= delete;
			Parser(Parser&&) noexcept				= delete;
			Parser& operator=(const Parser&)		= delete;
			Parser& operator=(Parser&&) noexcept	= delete;
			~Parser() noexcept						= default;

			

			std::vector<Content> Parse();

		private:
			enum class GroupMode { Root, Recursive };
			void consume_whitespaces();
			std::string parse_name();
			std::string parse_integer_content(const std::string& name);
			std::string parse_string_content(const std::string& name);
			std::string parse_group_content(const std::string& group_name);
			void check_semicolon_at_end(const std::string& name, const std::string& fragment);
			Item::Type 	guess_type(const std::string& name);
			bool		check_next_read_available();

			std::istream& m_stream;
			GroupMode m_group_mode;
	};
}