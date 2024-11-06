#include <StormByte/config/exception.hxx>
#include <StormByte/config/file.hxx>
#include <StormByte/config/parser.hxx>

#include <fstream>
#include <sstream>

using namespace StormByte::Config;

File::File(const std::filesystem::path& file):m_file(file) {
	m_root = std::make_unique<Group>("root");
}

File::File(std::filesystem::path&& file):m_file(std::move(file)) {
	m_root = std::make_unique<Group>("root");
}

File::File(const File& file):m_file(file.m_file) {
	m_root = std::make_unique<Group>(*file.m_root);
}

File& File::operator=(const File& file) {
	if (this != &file) {
		m_file = file.m_file;
		m_root = std::make_unique<Group>(*file.m_root);
	}
	return *this;
}

std::shared_ptr<Item> File::Add(const std::string& name, const Item::Type& type) {
	return m_root->Add(name, type);
}

void File::Clear() noexcept { m_root = std::make_unique<Group>("root"); }

void File::Read() {
	Clear();
	std::ifstream file;
	file.open(m_file, std::ios::in);
	if (file.fail())
		throw FileIOError(m_file.string(), "read");
	try {
		Parser parser(std::move(file), Parser::GroupMode::Root);
		std::vector<Parser::Content> parsed_content = parser.Parse();
		Add(m_root.get(), std::move(parsed_content));
	}
	catch (const ParseError& pe) {
		throw pe;
	}

	this->PostRead();
}

void File::ReadFromString(const std::string& cfg_str) {
	Clear();
	try {
		std::istringstream is(cfg_str);
		Parser parser(std::move(is), Parser::GroupMode::Root);
		std::vector<Parser::Content> parsed_content = parser.Parse();
		Add(m_root.get(), std::move(parsed_content));
	}
	catch (const ParseError& pe) {
		throw pe;
	}

	this->PostRead();
}

void File::PostRead() noexcept {}

void File::Write() {
	std::ofstream file;
	file.open(m_file, std::ios::out);
	if (file.fail())
		throw FileIOError(m_file.string(), "write");
	
	for (auto it = m_root->m_children.rbegin(); it != m_root->m_children.rend(); it++)
		file << it->second->Serialize(0) << "\n";

	file.close();
}

std::shared_ptr<Item> File::LookUp(const std::string& path) const {
	return m_root->LookUp(path);
}

void File::Add(Item* parent, Parser::Content&& content) {
	std::shared_ptr<Item> child;
	try {
		child = parent->Add(content.s_name, content.s_type);
	}
	catch(const InvalidName&) {
		throw ParseError(content.s_name, content.s_content, "Invalid name");
	}
	switch (content.s_type) {
		case Item::Type::Integer:
			try {
				child->SetInteger(std::stoi(content.s_content));
			}
			catch(const std::invalid_argument&) {
				throw ParseError(content.s_name, content.s_content, "Bad integer value");
			}
			catch(const std::out_of_range&) {
				throw ParseError(content.s_name, content.s_content, "Out of range");
			}
			break;

		case Item::Type::String:
			try {
				child->SetString(std::move(content.s_content));
			}
			catch (const InvalidName&) {
				throw ParseError(content.s_name, content.s_content, "Invalid name");
			}
			break;

		case Item::Type::Group:
			try {
				std::istringstream is(std::move(content.s_content));
				Parser group_parser(std::move(is), Parser::GroupMode::Recursive);
				Add(child.get(), group_parser.Parse());
			}
			catch(const ParseError& pe) {
				throw pe;
			}
	}
}

void File::Add(Item* parent, std::vector<Parser::Content>&& contents) {
	for (auto it = contents.begin(); it != contents.end(); it++)
		Add(parent, std::move(*it));
}