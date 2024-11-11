#pragma once

#include <StormByte/visibility.h>

#include <memory>

namespace StormByte::System {
	class Executable;
	class STORMBYTE_PUBLIC Worker {
		public:
			Worker(std::unique_ptr<Process>&&);
			Worker(const Worker&)				= delete;
			Worker(Worker&&)					= default;
			Worker& operator=(const Worker&)	= delete;
			Worker& operator=(Worker&&)			= default;
			~Worker()							= default;

		private:
			std::unique_ptr<Process> m_executable;
	};
}