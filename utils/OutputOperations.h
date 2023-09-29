#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <libds/heap_monitor.h>

inline void odsad(std::string& slovo, size_t odsadenie)
{
    int m = odsadenie - slovo.length();
    if (m > 1)
    {
        std::string pomocna;
        int delitel1;
        int delitel2;
        if (m % 2 == 0)
        {
            delitel1 = delitel2 = m / 2;
        }
        else
        {
            delitel1 = m / 2;
            delitel2 = m / 2 + 1;
        }
        for (int i = 0; i < delitel1; ++i)
        {
            pomocna += " ";
        }
        pomocna += slovo;
        for (int i = 0; i < delitel2 - 1; ++i)
        {
            pomocna += " ";
        }
        pomocna += "|";
        slovo = pomocna;
    }
}

inline void vypis(std::string string)
{
    std::string vystup;
    std::stringstream stream(string);
    std::string sortN, code, officialTitle, mediumTitle, shortTitle, note, population;
    std::getline(stream, sortN, ';');
    std::getline(stream, code, ';');
    std::getline(stream, officialTitle, ';');
    std::getline(stream, mediumTitle, ';');
    std::getline(stream, shortTitle, ';');
    std::getline(stream, note, ';');
    std::getline(stream, population);
    odsad(sortN, 6);
    odsad(code, 20);
    odsad(officialTitle, 50);
    odsad(mediumTitle, 31);
    odsad(shortTitle, 30);
    odsad(note, 10);
    odsad(population, 20);
    vystup += sortN += code += officialTitle += mediumTitle += shortTitle += note += population;
    std::cout << vystup << std::endl;
}


