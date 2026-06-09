/*
 * Made by Gabriel Barnard
 * Updated on the 9th of June 2026
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cstdio>

#include "../inc/CSVprocessor.hpp"

CSVprocessor::CSVprocessor(const std::string &filePath) : filePath(filePath) {
    loadData(CSVprocessor::filePath);
}

void CSVprocessor::crudCreate(const Stock &userInput) {
    int entryId{};

    // Searches through the HashTable for the lowest non-occupied Id
    while (stocks.find(entryId) != stocks.end()) {
        entryId++;
    }

    stocks[entryId].id = entryId;
    stocks[entryId].name = userInput.name;
    stocks[entryId].price = userInput.price;
    stocks[entryId].entryDate = userInput.entryDate;
}

const std::vector<CSVprocessor::Stock> CSVprocessor::crudRead(const Stock &userInput) {
    if (userInput.id == -1) { // Returns all stocks in HashTable (user left stockID empty)
        std::vector<CSVprocessor::Stock> stocksToReturn;
        std::vector<int> keys;

        for (const auto &[key, stock] : stocks) {
            keys.push_back(key);
        }

        std::sort(keys.begin(), keys.end());

        for (const auto &key : keys) {
            stocksToReturn.push_back(stocks.at(key));
        }

        return stocksToReturn;

    } else if (stocks.find(userInput.id) == stocks.end()) {
        throw std::runtime_error("Invalid Stock ID");
    } else {                  // Returns one stock in HashTable
        CSVprocessor::Stock stockToReturn = stocks.at(userInput.id);
        return {stockToReturn};
    }

    return {}; // Should not trigger unless something goes wrong
}

void CSVprocessor::crudUpdate(const Stock &userInput) {
    if (stocks.find(userInput.id) == stocks.end()) {
        throw std::runtime_error("Invalid Stock ID");
    }

    stocks[userInput.id].name = userInput.name;
    stocks[userInput.id].entryDate = userInput.entryDate;
    stocks[userInput.id].price = userInput.price;
}

void CSVprocessor::crudDelete(const Stock &userInput) {
    if (stocks.find(userInput.id) == stocks.end()) {
        throw std::runtime_error("Invalid Stock ID");
    }

    stocks.erase(userInput.id);
}

// TODO: Input more file validation here, and better handling in CSVwindow
void CSVprocessor::loadData(const std::string &filePath) {
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

        // Places the data from the CSV file into the Stock
        stock.id = std::stoi(parts[0]);
        stock.name = parts[1];
        stock.price = std::stod(parts[2]);
        stock.entryDate = parts[3];

        // Places the new stock into the HashTable
        stocks[stock.id] = stock;
    }

    inputStream.close();
}

void CSVprocessor::close(void) {
    writeData(filePath);
}

void CSVprocessor::writeData(const std::string &filePath) {
    std::string tempFilePath{filePath + ".temp"};

    std::ofstream outputStream(tempFilePath);
    if (!outputStream.is_open()) {
        throw std::runtime_error("An error occured when calling CSVprocessor's destructor. Unable to open temporary.csv file.");
    }

    // Writes all stocks in the HashTable into the output stream
    for (const auto &[key, stock] : stocks) {
        outputStream << stock.id << ',' << stock.name << ',' << stock.price << ',' << stock.entryDate << '\n';
    }

    outputStream.close();

    // Adds .backup to the end of the original file
    if (std::rename(filePath.c_str(), (filePath + ".backup").c_str())) {
        throw std::runtime_error("An error occured when remaining .csv.temp to .csv in writeData(std::string filePath)");
    }

    // Renames the .csv.temp file to the original file name
    if (std::rename(tempFilePath.c_str(), filePath.c_str())) {
        throw std::runtime_error("An error occured when remaining .csv.temp to .csv in writeData(std::string filePath)");
    }
}
