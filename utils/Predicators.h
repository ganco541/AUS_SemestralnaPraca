#pragma once
#include <string>
#include <libds/heap_monitor.h>

inline bool startsWithStr(const std::string& title, std::string& findUpper)
{
    return title._Starts_with(findUpper);
}

inline bool containsStr(const std::string& title, std::string& findUpper)
{
    return title.find(findUpper) != std::string::npos;
}

inline bool hasType(const size_t& type, size_t& inputType)
{
    return type == inputType;
}

inline bool popMoreThan(const size_t& population, size_t& inputPop)
{
    return inputPop < population;
}