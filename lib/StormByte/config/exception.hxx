#pragma once

#include <StormByte/config/item.hxx>
#include <StormByte/exception.hxx>

namespace StormByte::Config {
	class STORMBYTE_PUBLIC WrongValueTypeConversion final: public Exception {
		public:
			WrongValueTypeConversion(const Item&, const std::string&);
			WrongValueTypeConversion(const WrongValueTypeConversion&)				= default;
			WrongValueTypeConversion& operator=(const WrongValueTypeConversion&)	= default;
			~WrongValueTypeConversion() noexcept override							= default;
	};

	class STORMBYTE_PUBLIC ValueFailure final: public Exception {
		public:
			ValueFailure(const Item&, const Item::Type&);
			ValueFailure(const ValueFailure&)				= default;
			ValueFailure& operator=(const ValueFailure&)	= default;
			~ValueFailure() noexcept override				= default;
	};

	class STORMBYTE_PUBLIC FileIOError final: public Exception {
		public:
			FileIOError(const std::string&, const std::string&);
			FileIOError(const FileIOError&)				= default;
			FileIOError& operator=(const FileIOError&)	= default;
			~FileIOError() noexcept override			= default;
	};
}