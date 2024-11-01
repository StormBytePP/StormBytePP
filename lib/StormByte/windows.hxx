#include "visibility.h"

#include <string>

namespace StormByte {
	class DLL_PUBLIC Windows {
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
	}
}