#include <StormByte/config/item/group.hxx>
#include <StormByte/config/item/value/integer.hxx>
#include <StormByte/config/item/value/string.hxx>
#include <StormByte/config/exception.hxx>

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
	if (find_if(name.begin(), name.end(), 
        [](char c) { return !isalnum(c); }) != name.end())
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