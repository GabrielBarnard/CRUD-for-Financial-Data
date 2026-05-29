/*
 * Made by Gabriel Barnard
 * Updated on the 29th of May 2026
 */

#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>

class CSVprocessor {
	private:
        struct Stock {
            std::time_t entryDate{};
            std::string name{};
            int id{};
            int price{};
		};
        std::unordered_map<int, Stock> stocks;
        void loadData(const std::string filePath);
		void writeData(void);
	public:
        void crudCreate(const Stock userInput);
        const std::vector<Stock> crudRead(const Stock userInput);
        void crudUpdate(const Stock userInput);
        void crudDelete(const Stock userInput);
	
        CSVprocessor(const std::string filePath);
		~CSVprocessor(void);
};
