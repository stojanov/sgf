#pragma once
#include <functional>
#include <mutex>
#include "Namespace.h"

SGF_NAMESPACE(::System)

static std::mutex LOG_IO_LOCK;

using voidCallback = std::function<void()>;

END_NAMESPACE
