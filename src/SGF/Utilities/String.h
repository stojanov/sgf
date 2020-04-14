#pragma once

#include <string>
#include <regex>
#include <vector>
#include "Namespace.h"

using std::string;

SGF_NAMESPACE(::Util::String)

static std::vector<string> split(const string& input, const string& regex)
{
	std::regex re(regex);
	std::sregex_token_iterator
		first{ input.begin(), input.end(), re, -1 },
		last;
	return { first, last };
}

static void ltrim(string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
		}));
}

static void rtrim(string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

static void trim(string& s)
{
	ltrim(s);
	rtrim(s);
}

static string copyTrim(string s)
{
	trim(s);
	return s;
}

END_NAMESPACE