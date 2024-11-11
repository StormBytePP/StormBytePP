#pragma once

#include <StormByte/visibility.h>


#include <memory>
#include <optional>
#include <string>
#include <vector>

#ifdef WINDOWS
#include <windows.h>
#else
#include <sys/poll.h>
#endif

namespace StormByte::System {
	class STORMBYTE_PRIVATE Pipe {
		public:
			static constexpr size_t MAX_READ_BYTES		= 4 * 1024 * 1024; // 4MiB

			Pipe();
			Pipe(const Pipe&)				= delete;
			Pipe(Pipe&&)					= default;
			Pipe& operator=(const Pipe&)	= delete;
			Pipe& operator=(Pipe&&)			= default;
			~Pipe() noexcept;

			#ifdef LINUX
			void bind_read(int) noexcept;
			void bind_read(Pipe&) noexcept;
			void bind_write(int) noexcept;
			void bind_write(Pipe&) noexcept;
			ssize_t write(const std::string&);
			bool write_eof() const;
			ssize_t read(std::vector<char>&, ssize_t) const;
			bool read_eof() const;
			#else
			void set_read_handle_information(DWORD, DWORD);
			void set_write_handle_information(DWORD, DWORD);
			HANDLE get_read_handle() const;
			HANDLE get_write_handle() const;
			DWORD write(const std::string&);
			DWORD read(std::vector<CHAR>&, DWORD) const;
			#endif
			bool write_atomic(std::string&&);
			void close_read() noexcept;
			void close_write() noexcept;

			Pipe& operator<<(const std::string&);
			std::string& operator>>(std::string&) const;

		private:
			#ifdef LINUX
			void bind(int&, int) noexcept;
			void close(int&) noexcept;
			#else
			void close(HANDLE&) noexcept;
			void set_handle_information(HANDLE, DWORD, DWORD);
			#endif

			#ifdef WINDOWS
			HANDLE m_fd[2];
			static SECURITY_ATTRIBUTES m_sAttr;
			#else
			int m_fd[2];
			#endif
			
	};
}