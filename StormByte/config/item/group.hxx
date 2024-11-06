#pragma once

#include <StormByte/config/item.hxx>

#include <map>
#include <queue>

namespace StormByte::Config {
	class STORMBYTE_PUBLIC Group final: public Item {
		friend class File;
		using Storage = std::map<std::string, std::shared_ptr<Item>>;
		public:
			class iterator;
			class const_iterator;
			Group(const std::string&);
			Group(std::string&&);
			Group(const Group&);
			Group(Group&&) noexcept				= default;
			Group& operator=(const Group&);
			Group& operator=(Group&&) noexcept	= default;
			~Group() noexcept override			= default;

			Storage::iterator			Begin() noexcept;
			Storage::const_iterator		Begin() const noexcept;
			Storage::iterator			End() noexcept;
			Storage::const_iterator 	End() const noexcept;

			Group&						AsGroup() override;
			const int& 					AsInteger() const override;
			const std::string& 			AsString() const override;

			std::shared_ptr<Item>		Add(const std::string&, const Type&);
			std::shared_ptr<Item>		Add(std::shared_ptr<Item>);					
			void						Remove(const std::string&);

			void						SetInteger(const int&) override;
			void						SetString(const std::string&) override;
			void						SetString(std::string&&) override;

			std::shared_ptr<Item>		Child(const std::string&) const;
			bool						Exists(const std::string&) const noexcept;
			std::shared_ptr<Item>		LookUp(const std::string&) const;

			std::string					Serialize(const int&) const noexcept override;

		private:
			std::shared_ptr<Item>		Clone() override;
			std::shared_ptr<Item>		LookUp(std::queue<std::string>&) const;
			bool						Exists(std::queue<std::string>&) const noexcept;
			std::queue<std::string> 	ExplodePath(const std::string&) const noexcept;

			std::map<std::string, std::shared_ptr<Item>> m_children;
	};
}