#pragma once
#include <string>
#include <libds/heap_monitor.h>
#include "Algorithm.h"

inline size_t vypocitajSamohlasky(const std::string& string)
{
    std::string samohlasky = "aáäeéiíyýoóôuú";
    size_t tmp{ 0 };
    algoritmus(string.begin(), string.end(),
        [&samohlasky](const char& c)
        {
            return samohlasky.find(tolower(c)) != std::string::npos;
        },
        [&tmp](const char& c)
        {
            ++tmp;
        });
    return tmp;
}
