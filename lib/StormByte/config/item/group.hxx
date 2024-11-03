#pragma once

#include <StormByte/config/item.hxx>

#include <map>
#include <queue>

namespace StormByte::Config {
	class STORMBYTE_PUBLIC Group final: public Item {
		friend class File;
		public:
			Group(const std::string&);
			Group(std::string&&);
			Group(const Group&);
			Group(Group&&) noexcept				= default;
			Group& operator=(const Group&);
			Group& operator=(Group&&) noexcept	= default;
			~Group() noexcept override	= default;

			Group&					AsGroup() override;
			const int& 				AsInteger() const override;
			const std::string& 		AsString() const override;

			std::shared_ptr<Item>	Add(const std::string&, const Type&) override;

			void					SetInteger(const int&) override;
			void					SetString(const std::string&) override;
			void					SetString(std::string&&) override;

			std::shared_ptr<Item>	LookUp(const std::string&) const;

			std::string				Serialize(const int&) const noexcept override;

		private:
			std::shared_ptr<Item>	Clone() override;
			std::shared_ptr<Item>	LookUp(std::queue<std::string>&) const;

			std::map<std::string, std::shared_ptr<Item>> m_children;
	};
}