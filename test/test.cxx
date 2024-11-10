#include <StormByte/log/file.hxx>

using namespace StormByte::Log;

int main() {
	File f(Level::Info, "/tmp/test.log");
	f << Level::Debug << "Debug test string" << Logger::endl;
	f << Level::Info << "Info test string" << Logger::endl;
	f << Level::Info << "Info test string" << " with more content" << Logger::endl;
	return 0;
}