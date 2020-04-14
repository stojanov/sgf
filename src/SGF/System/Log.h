#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <mutex>

using std::lock_guard;
using std::mutex;
using std::stringstream;
using std::time;

enum LogLevel
{
	DEBUG = 1,
	INFO,
	WARN,
	ERROR,
	NONE
};
constexpr int LOG_LEVEL = DEBUG;
//#define LOG_SYNC_IO

#ifdef LOG_SYNC_IO
#include "Core.h"
#endif

/*
 * Very basic logger
 * Doesn't save log output to file
 * Only serves as a runtime logger
 */
class Logger
{
public:
	Logger(LogLevel lvl, const std::string& name = "")
		: m_Level(lvl)
	{
		auto t = time(nullptr);
		const auto tm = std::localtime(&t);
		
		if (m_Level >= LOG_LEVEL)
		{
			m_SS
				<< (!name.empty() ? "[" + name + "]\t" : "")
				<< '[' << getLabel(m_Level) << "]\t"
				<< std::put_time(tm, "%H:%M:%S")
				<< ' ';
		}
	}

	~Logger()
	{
	// std::endl is used to force flush on the stream
#ifdef LOG_SYNC_IO
		const lock_guard<mutex> lock(sgf::System::LOG_IO_LOCK);
		std::cout << m_SS.str() << std::endl;
#else 
		std::cout << m_SS.str() << std::endl;
#endif
	}

	template<typename T>
	constexpr Logger& operator<< (const T& o)
	{
		if (m_Level >= LOG_LEVEL)
		{
			m_SS << o;
		}
		return *this;
	}

private:
	LogLevel m_Level;
	stringstream m_SS;
	
	static constexpr const char* getLabel(LogLevel lvl)
	{
		switch (lvl) {
			case DEBUG: return "DEBUG";
			case INFO:  return "INFO";
			case WARN:  return "WARN";
			case ERROR: return "ERROR";
			default: return "";
		}
	}
};

#ifndef NDEBUG
#define Log Logger
#else
#define Log __noop
#endif

#define DLOG Log(DEBUG)
#define ILOG Log(INFO)
#define WLOG Log(WARN)
#define ELOG Log(ERROR)