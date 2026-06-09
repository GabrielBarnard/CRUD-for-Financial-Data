/*
 * Made by Gabriel Barnard
 * Updated on the 9th of June 2026
 */

#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>

class CSVprocessor {
	public:
        struct Stock {
            std::string entryDate{};
            std::string name{};
            int id{};
            double price{};
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
