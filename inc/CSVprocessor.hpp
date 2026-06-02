/*
 * Made by Gabriel Barnard
 * Updated on the 31st of May 2026
 */

#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>

class CSVprocessor {
	public:
        struct Stock {
            std::time_t entryDate{}; // TODO: Update to String, there's no actual reason (in this scenario) to use time_t
            std::string name{};
            int id{};
            int price{}; // TODO: Update to double
        };

        void crudCreate(const Stock &userInput);
        const std::vector<Stock> crudRead(const Stock &userInput);
        void crudUpdate(const Stock &userInput);
        void crudDelete(const Stock &userInput);

        void close(void);

        CSVprocessor(const std::string &filePath);
    private:
        void writeData(const std::string &filePath);
        const std::string filePath;
        std::unordered_map<int, Stock> stocks;
        void loadData(const std::string &filePath);
};
