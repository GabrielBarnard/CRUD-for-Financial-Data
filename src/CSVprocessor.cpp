/*
 * Made by Gabriel Barnard
 * Updated on the 29th of May 2026
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "../inc/CSVprocessor.hpp"

CSVprocessor::CSVprocessor(const std::string filePath) {
    loadData(filePath);
}

CSVprocessor::~CSVprocessor(void) {
	writeData();
}

void CSVprocessor::crudCreate(const Stock userInput) {

}

const std::vector<CSVprocessor::Stock> CSVprocessor::crudRead(const Stock userInput) {
	return {};
}

void CSVprocessor::crudUpdate(const Stock userInput) {

}

void CSVprocessor::crudDelete(const Stock userInput) {

}

void CSVprocessor::loadData(const std::string filePath) {
    // Opens an input file stream to the CSV file and verifies that it opened successfully
    std::ifstream inputStream(filePath);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Error: Unable to open the CSV file \"" + filePath + "\"");
    }

    std::string line;
    // Loops through all lines in the CSV file
    while (std::getline(inputStream, line)) {
        // If there is a carriage return (windows-style CSV), removes it
        if (line.back() == '\r') {
            line.pop_back();
        } else {
            // Deliberate NOP (No Operation)
        }

        std::vector<std::string> parts{};
        std::string part{};
        for (const auto& character : line) {
            if (character != ',') {
                part.append(1, character);
            } else {
                parts.push_back(part);
                part = {};
            }
        }
        parts.push_back(part);

        CSVprocessor::Stock stock{};

        stock.id = std::stoi(parts[0]);
        stock.name = parts[1];
        stock.price = std::stoi(parts[2]);

        struct std::tm tm{};
        std::istringstream ss(parts[3]);
        ss >> std::get_time(&tm, "%Y-%m-%d");

        if (ss.fail()) {
            throw std::runtime_error("Error loading CSV file. Likely an issue with CSV file formatting");
        }

        stock.entryDate = std::mktime(&tm);

        stocks[stock.id] = stock;
    }

    inputStream.close();
}

void CSVprocessor::writeData(void) {

}
