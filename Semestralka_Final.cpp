#include <iostream>
#include "structure/Hierarchy.h"
#include "structure/Tables.h"
#include "structure/Sequences.h"
#include <Windows.h>
#include <libds/heap_monitor.h>

int main()
{
    initHeapMonitor();
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    std::setlocale(LC_ALL, "");
    Sequences* sequences = new Sequences{ "csv/kraje.csv", "csv/okresy.csv", "csv/obce.csv" };
    Hierarchy* hierarchy = new Hierarchy{ sequences->getKraje(), sequences->getOkresy(), sequences->getObce() };
    hierarchy->setPopulation("csv/obyvatelstvo.csv");
    Tables* tables = new Tables{hierarchy->getHierarchy()};
    bool end{ false };
    bool deeper{ false };
    bool operation{ false };
    bool tableSearch{ false };
    size_t input{ 0 };
    std::string inputString{ "" };
    while (!end)
    {
        while (!end && !deeper && !operation && !tableSearch)
        {
            std::cout << "///////////////////////////////////\n" << "Your location: " << hierarchy->getCurrentOfficialTitle() << "\n///////////////////////////////////\n";
            std::cout << "(1) List sons\n(2) Jump to son\n(3) Operations\n(4) Search table\n(5) Back\n(6) Exit\n------------------------------------\nChoose an option: ";
            std::cin >> input;
            switch (input)
            {
            case 1:
                hierarchy->printSons();
                break;
            case 2:
                deeper = true;
                break;
            case 3:
                operation = true;
                break;
            case 4:
                tableSearch = true;
                break;
            case 5:
                hierarchy->moveUp();
                break;
            case 6:
                end = true;
                break;
            }
        }
        while (deeper)
        {
            size_t numberOfSons{0};
            if (hierarchy->canMoveDown(numberOfSons))
            {
                std::cout << "------------------------------------\n";
                std::cout << "Please chose to which location you want to go: ";
                std::cin >> input;
                if (0 < input && input <= numberOfSons)
                {
                    hierarchy->moveDown(input);
                    deeper = false;
                }
                else
                {
                    std::cout << "------------------------------------\n";
                    std::cout << "Location under that ID doesn't exist!\n";
                }
            }
            else
            {
                deeper = false;
            }
        }
        while (operation)
        {
            std::cout << "------------------------------------\n";
            std::cout << "(1) startsWithStr\n(2) containsStr\n(3) hasType\n(4) popMoreThan\n(5) Back\n";
            std::cout << "------------------------------------\n";
            std::cout << "Choose your operation: ";
            std::cin >> input;
            if (input > 0 && input < 5)
            {
                if (input == 1 || input == 2)
                {
                    std::cout << "------------------------------------\n";
                    std::cout << "Write your string: ";
                    std::getline(std::cin >> std::ws, inputString);
                    std::transform(inputString.begin(), inputString.end(), inputString.begin(), [](unsigned char c) {return std::toupper(c); });
                }
                else if (input == 3)
                {
                    bool error{ true };
                    while (error)
                    {
                        std::cout << "------------------------------------\n(1) kraje\n(2) okresy\n(3) obce\n------------------------------------\nChoose from above: ";
                        std::getline(std::cin >> std::ws, inputString);
                        if (inputString == "1" || inputString == "2" || inputString == "3")
                        {
                            error = false;
                        }
                    }
                }
                else
                {
                    bool error{ true };
                    while (error)
                    {
                        std::cout << "------------------------------------\n";
                        std::cout << "Write what number should the population be more than: ";
                        std::getline(std::cin >> std::ws, inputString);
                        std::string chars = "A¡ƒBC»DœE…FGHCHIÕJKL≈ºMN“O”‘PQR¿SäTçU⁄VWXY›Zé.[$&+,:;=?@#|'<>.-^*()%!]";
                        std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::toupper);
                        bool tmp{ false };
                        for (size_t i = 0; i < inputString.length(); ++i)
                        {
                            if (chars.find(inputString.at(i)) != std::string::npos)
                            {
                                tmp = true;
                                break;
                            }
                        }
                        
                       error = tmp;
                    }
                }
                hierarchy->doPredicate(inputString, input);
            }
            else if (input == 5)
            {
                operation = false;
            }
        }
        while (tableSearch)
        {
            std::cout << "------------------------------------\n";
            std::cout << "(1) kraje\n(2) okresy\n(3) obce\n(4) Back\n";
            std::cout << "------------------------------------\n";
            std::cout << "Choose table from above: ";
            std::cin >> input;
            if (input > 0 && input < 4)
            {
                tables->setTable(input);
                std::cout << "------------------------------------\n";
                std::cout << "Please write your search key (name): ";
                std::getline(std::cin >> std::ws, inputString);
                std::transform(inputString.begin(), inputString.end(), inputString.begin(), [](unsigned char c) {return std::toupper(c); });
                tables->findAndPrint(inputString, hierarchy->getHierarchy());
            }
            else if (input == 4)
            {
                tableSearch = false;
            }
            else
            {
                std::cout << "Please choose an option!\n";
            }
        }
    }
    delete sequences;
    delete hierarchy;
    delete tables;
}

