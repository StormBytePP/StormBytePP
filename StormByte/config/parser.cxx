#include "StormByte/config/exception.hxx"
#include "StormByte/config/parser.hxx"

using namespace StormByte::Config;

Parser::Parser(std::ifstream&& stream, const GroupMode& gm):m_stream(stream), m_group_mode(gm) {}

Parser::Parser(std::istringstream&& stream, const GroupMode& gm):m_stream(stream), m_group_mode(gm) {}

std::vector<Parser::Content> Parser::Parse() {
	std::vector<Content> parsed_content;
	try {
		int control = m_stream.peek();
		if (control == EOF)
			return parsed_content;

		do {
			std::string name, content;
			Item::Type type;
			name = parse_name();
			switch (guess_type(name)) {
				case Item::Type::Integer:
					type = Item::Type::Integer;
					content = parse_integer_content(name);
					break;

				case Item::Type::String:
					type = Item::Type::String;
					content = parse_string_content(name);
					break;

				case Item::Type::Group:
					type = Item::Type::Group;
					content = parse_group_content(name);
					break;
			}

			// If we reached here without exception we can assume data is valid
			parsed_content.push_back({std::move(name), type, std::move(content)});
			consume_whitespaces();
			control = m_stream.peek();
			// We check if next character is EOF in which case we end now
		} while(!m_stream.eof() && control != EOF);
	}
	catch(const ParseError& pe) {
		throw pe;
	}

	return parsed_content;
}

void Parser::consume_whitespaces() {
	bool halt = false;
	do {
		int control = m_stream.peek();
		if (control == EOF) return;

		char c;
		m_stream.get(c);
		switch(c) {
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				continue;
			default:
				halt = true;
				m_stream.seekg(-1, std::ios::cur);
		}
	} while(!m_stream.eof() && !halt);
}

std::string Parser::parse_group_content(const std::string& group_name) {
	/* If in root mode, we need to parse the starting { and ending } with ; */
	/* But in recursive mode we skip those */
	std::string fragment = "";
	int level = 0;
	do {
		consume_whitespaces();
		if (!m_stream.eof()) {
			char c;
			m_stream.get(c);
			switch(c) {
				case '{':
					if (level++ > 0)
						fragment += '{';
					break;

				case '}':
					if (--level > 0)
						fragment += '}';
					break;

				default:
					fragment += c;
			}
		}
	} while(!m_stream.eof() && level > 0);
	if (level == 0) {
		if (m_group_mode == GroupMode::Root) {
			check_semicolon_at_end(group_name, fragment);
		}
		else {
			/* We "check" for semicolon but ignore the exception and do not add the ; */
			try {
				check_semicolon_at_end(group_name, fragment);
			}
			catch(const ParseError&) {
			}
		}
	}
	else // We had a problem
		throw ParseError(group_name, fragment);

	return fragment;
}

std::string Parser::parse_name() {
	std::string fragment = "";
	bool halt = false;
	do {
		consume_whitespaces();
		if (!m_stream.eof()) {
			char c;
			m_stream.get(c);
			switch(c) {
				case '=':
					halt = true;
					break;

				default: {
					if (std::isalnum(c) || c == '_')
						fragment += c;
					else {
						throw ParseError(fragment);
					}
				}
			}
		}
	} while (!m_stream.eof() && !halt);

	return fragment;
}

Item::Type Parser::guess_type(const std::string& name) {
	Item::Type type;
	consume_whitespaces();
	m_stream.peek();
	if (!m_stream.eof()) {
		char c;
		m_stream.get(c);
		if (std::isdigit(c)) {
			type = Item::Type::Integer;
		}
		else if (c == '"') {
			type = Item::Type::String;
		}
		else if (c == '{') {
			type = Item::Type::Group;
		}
		else
			throw ParseError(name, {1, c});

		m_stream.seekg(-1, std::ios::cur);
	}
	else
		throw ParseError(name);

	return type;
}

std::string Parser::parse_string_content(const std::string& name) {
	std::string fragment = "";
	bool halt = false;
	bool str_opened = false;
	char c;
	do {
		m_stream.get(c);
		switch (c) {
			case '"':
				if (str_opened) {
					halt = true;
					str_opened = false;
				}
				else
					str_opened = true;
				break;

			default:
				fragment += c;
		}
	} while (!m_stream.eof() && !halt);
	if (str_opened)
		throw ParseError(name, fragment);

	check_semicolon_at_end(name, fragment);

	return fragment;
}

std::string Parser::parse_integer_content(const std::string& name) {
	std::string fragment = "";
	bool halt = false;
	do {
		consume_whitespaces();
		char c;
		m_stream.get(c);
		if (std::isdigit(c))
			fragment += c;
		else if (c == ';') {
			halt = true;
			m_stream.seekg(-1, std::ios::cur);
		}
		else
			throw ParseError(name, fragment);
	} while (!m_stream.eof() && !halt);

	check_semicolon_at_end(name, fragment);

	return fragment;
}

void Parser::check_semicolon_at_end(const std::string& name, const std::string& fragment) {
	bool missing_semicolon = false;
	char c;
	consume_whitespaces();
	if (!m_stream.eof()) {
		m_stream.get(c);
		if (c != ';') missing_semicolon = true;
	}
	else
		missing_semicolon = true;

	if (missing_semicolon)
		throw ParseError(name, fragment, "Missing semicolon at the end");
}
