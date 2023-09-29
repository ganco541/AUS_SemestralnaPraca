#pragma once
#include <string>
#include <locale>
#include <libds/heap_monitor.h>
#include "Other.h"

inline int compareAlphabetical(const std::string& title1, const std::string& title2, std::locale& loc)
{
	if (loc(title1, title2))
	{
		return -1;
	}
	else if (title1 == title2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

inline int compareVowelsCount(const std::string& title1, const std::string& title2)
{
	size_t s1 = vypocitajSamohlasky(title1);
	size_t s2 = vypocitajSamohlasky(title2);
	if (s1 < s2)
	{
		return -1;
	}
	else if (s1 == s2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}