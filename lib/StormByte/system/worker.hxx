#pragma once

#include <StormByte/visibility.h>

#include <memory>

namespace StormByte::System {
	class Executable;
	class STORMBYTE_PUBLIC Worker {
		public:
			Worker(std::unique_ptr<Executable>&&);
			Worker(const Worker&)				= delete;
			Worker(Worker&&)					= default;
			Worker& operator=(const Worker&)	= delete;
			Worker& operator=(Worker&&)			= default;
			~Worker()							= default;

		private:
			std::unique_ptr<Executable> m_executable;
	};
}