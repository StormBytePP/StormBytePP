#include <StormByte/config/exception.hxx>
#include <StormByte/config/file.hxx>
#include <StormByte/config/item/group.hxx>

#include <fstream>

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

void File::Clear() noexcept { m_root.reset(); }

void File::Read() {
	/* This is gonna be a bit hard... */
}

void File::Write() {
	std::ofstream file;
	file.open(m_file, std::ios::out);
	if (file.fail())
		throw FileIOError(m_file, "write");
	
	for (auto it = m_root->m_children.rbegin(); it != m_root->m_children.rend(); it++)
		file << it->second->Serialize(0) << "\n";

	file.close();
}
