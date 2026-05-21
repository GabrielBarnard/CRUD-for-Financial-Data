/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#pragma once

#include <vector>
#include <string>
#include <ctime>

class SQLprocessor {
private:
    struct stock {
        std::time_t entryDate{};
        std::string stockName{};
        int stockID{};
        int stockPrice{};
    };
public:
    void crudCreate(const stock userInput);
    const std::vector<stock> crudRead(const stock userInput);
    void crudUpdate(const stock userInput);
    void crudDelete(const stock userInput);
};
