#pragma once

#include <StormByte/config/item.hxx>

namespace StormByte::Config {
	class STORMBYTE_PUBLIC Value: public Item {
		public:
			Value(const Type&, const std::string&);
			Value(const Type&, std::string&&);
			Value(const Value&)					= default;
			Value(Value&&) noexcept				= default;
			Value& operator=(const Value&)		= default;
			Value& operator=(Value&&) noexcept	= default;
			~Value() noexcept override			= default;

			Group&				 	AsGroup() override;
			std::shared_ptr<Item>	Add(const std::string&, const Type&) override;
	};
}