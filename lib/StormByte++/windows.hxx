#include <StormByte++/visibility.h>

#include <string>
#include <tchar.h>
#include <windows.h>

namespace StormBytePP {
	class STORMBYTE_PUBLIC Windows {
		public:
			static const std::string			ExpandEnvironmentVariable(const std::string&);
			static const std::string			ExpandEnvironmentVariable(const std::wstring&);
			static std::string					UTF8Encode(const std::wstring&);
			static std::wstring					UTF8Decode(const std::string&);

		private:
			Windows()							= delete;
			Windows(const Windows&)				= delete;
			Windows(Windows&&)					= delete;
			Windows& operator=(const Windows&)	= delete;
			Windows& operator=(Windows&)		= delete;
			~Windows()							= delete;
	};
}