#include "IO.h"
#include "System/Log.h"
#include "System/Debug.h"

#include <fstream>

SGF_NAMESPACE(::Util::IO)

std::string ReadFile(const std::string& filePath)
{
	const std::ifstream file(filePath);

	if (!file.is_open())
	{
		ELOG << "Cannot load file:" << filePath;
		TRACE("Cannot load file");
	}

	std::ostringstream stream;
	
	stream << file.rdbuf();

	return stream.str();
}

std::future<std::string> AsyncReadFile(const std::string& filePath)
{
	return std::async(std::launch::async, std::bind(&ReadFile, filePath));
}
	
END_NAMESPACE
