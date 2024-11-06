#include <StormByte/config/item/group.hxx>
#include <StormByte/config/item/value/integer.hxx>
#include <StormByte/config/item/value/string.hxx>
#include <StormByte/config/exception.hxx>

#include <algorithm>
#include <sstream>

using namespace StormByte::Config;

Group::Group(const std::string& name):
Item(Type::Group, name) {}

Group::Group(std::string&& name):
Item(Type::Group, std::move(name)) {}

Group::Group(const Group& gr):Item(gr) {
	for (auto it = gr.m_children.begin(); it != gr.m_children.end(); it++)
		m_children.insert({ it->first, it->second->Clone() });
}

Group& Group::operator=(const Group& gr) {
	if (this != &gr) {
		Item::operator=(gr);
		m_children.clear();
		for (auto it = gr.m_children.begin(); it != gr.m_children.end(); it++)
			m_children.insert({ it->first, it->second->Clone() });
	}
	return *this;
}

Group& Group::AsGroup() {
	return *this;
}

const std::string& Group::AsString() const {
	throw WrongValueTypeConversion(*this, "AsString");
}

const int& Group::AsInteger() const {
	throw WrongValueTypeConversion(*this, "AsInt");
}

std::shared_ptr<Item> Group::Add(const std::string& name, const Type& type) {
	if (std::find_if(name.begin(), name.end(), 
        [](char c) { return !(isalnum(c) || c == '_'); }) != name.end())
		throw InvalidName(name);

	std::shared_ptr<Item> item;
	switch (type) {
		case Type::Group:
			item = std::make_shared<Group>(name);
			break;

		case Type::Integer:
			item = std::make_shared<Integer>(name);
			break;

		case Type::String:
			item = std::make_shared<String>(name);
			break;
	}
	m_children.insert({name, item});
	return item;
}

void Group::SetInteger(const int&) {
	throw ValueFailure(*this, Type::Integer);
}

void Group::SetString(const std::string&) {
	throw ValueFailure(*this, Type::String);
}

void Group::SetString(std::string&&) {
	throw ValueFailure(*this, Type::String);
}

bool Group::Exists(const std::string& path) const noexcept {
	std::queue<std::string> exploded_path = ExplodePath(path);
	return Exists(exploded_path);
}

std::shared_ptr<Item> Group::LookUp(const std::string& path) const {
	std::shared_ptr<Item> lookup_item;
	std::queue<std::string> exploded_path = ExplodePath(path);
	try {
		lookup_item = LookUp(exploded_path);
	} catch(const std::runtime_error&) {
		throw ItemNotFound(path);
	}
    return lookup_item;
}

std::shared_ptr<Item> Group::Child(const std::string& path) const {
	std::shared_ptr<Item> item;
	if (m_children.find(path) != m_children.end())
		item = m_children.at(path);
	return item;
}

std::string Group::Serialize(const int& indent_level) const noexcept {
	std::string serial = Indent(indent_level) + m_name + " = {\n";
	for (auto it = m_children.begin(); it != m_children.end(); it++) {
		serial += it->second->Serialize(indent_level + 1) + "\n";
	}
	serial += Indent(indent_level) + "};";
	return serial;
}

std::shared_ptr<Item> Group::Clone() {
	return std::make_shared<Group>(*this);
}

std::shared_ptr<Item> Group::LookUp(std::queue<std::string>& path) const {
	bool not_found = false;
	std::shared_ptr<Item> found_item;
	if (path.size() > 0) {
		std::string item_path = path.front();
		path.pop();

		if (m_children.find(item_path) != m_children.end()) {
			found_item = m_children.at(item_path);
			if (path.size() == 0)
				return found_item;
			else if (found_item->GetType() != Item::Type::Group)
				not_found = true;
			else
				return std::dynamic_pointer_cast<Group>(found_item)->LookUp(path);
		}
		else
			not_found = true;
	}
	else
		not_found = true;

	if (not_found)
		throw std::runtime_error("blasafel"); // Caller will throw the correct exception

	return found_item; // Just to make compiler warning away
}

bool Group::Exists(std::queue<std::string>& path) const noexcept {
	bool found = false;
	if (path.size() > 0) {
		std::string item_path = path.front();
		path.pop();

		if (m_children.find(item_path) != m_children.end()) {
			std::shared_ptr<Item> item = m_children.at(item_path);
			if (path.size() == 0)
				found = true;
			else if (item->GetType() != Item::Type::Group)
				found = false;
			else
				found = std::dynamic_pointer_cast<Group>(item)->Exists(path);
		}
	}
	return found;
}

std::queue<std::string> Group::ExplodePath(const std::string& path) const noexcept {
	std::queue<std::string> result;
    std::stringstream ss(path);
    std::string item;

    while (std::getline(ss, item, '/')) {
        result.push(item);
    }

	return result;
}