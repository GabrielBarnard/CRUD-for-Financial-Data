/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
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
			std::string stockName{};
			int stockID{};
			int stockPrice{};
		};
        std::unordered_map<int, Stock> stocks;
		void writeData(void);
	public:
        void crudCreate(const Stock userInput);
        const std::vector<Stock> crudRead(const Stock userInput);
        void crudUpdate(const Stock userInput);
        void crudDelete(const Stock userInput);
	
        CSVprocessor(const std::string filePath);
		~CSVprocessor(void);
};
