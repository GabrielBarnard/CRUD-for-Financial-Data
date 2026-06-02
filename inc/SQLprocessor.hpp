/*
 * Made by Gabriel Barnard
 * Updated on the 2nd of June 2026
 */

#pragma once

#include <sqlite3.h>

#include <vector>
#include <string>
#include <ctime>

class SQLprocessor {
    public:
        SQLprocessor(const std::string filepath);
        ~SQLprocessor(void);

        struct Stock {
            std::string entryDate{};
            std::string name{};
            int id{};
            double price{};
        };

        void crudCreate(const Stock userInput);
        const std::vector<Stock> crudRead(const Stock userInput);
        void crudUpdate(const Stock userInput);
        void crudDelete(const Stock userInput);
    private:
        sqlite3* db = nullptr;
};
