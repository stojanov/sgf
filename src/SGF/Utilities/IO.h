#pragma once

#include <string>
#include <memory>
#include <future>
#include "Namespace.h"

SGF_NAMESPACE(::Util::IO)

std::string ReadFile(const std::string& filePath);
std::future<std::string> AsyncReadFile(const std::string& filePath);
	
END_NAMESPACE