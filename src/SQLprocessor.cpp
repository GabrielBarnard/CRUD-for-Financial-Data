/*
 * Made by Gabriel Barnard
 * Updated on the 2nd of June 2026
 */

#include "../inc/SQLprocessor.hpp"

#include <stdexcept>

SQLprocessor::SQLprocessor (const std::string filePath) {
    // TODO: Validate SQL file here

    if (sqlite3_open(filePath.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Unable to open SQLite3 database.");
    }
}

SQLprocessor::~SQLprocessor (void) {
    sqlite3_close(db);
}

// Create
void SQLprocessor::crudCreate(const Stock userInput) {
    const char* sqlQuery = "INSERT INTO stocks (name, price, date) VALUES (?, ?, ?)";
    sqlite3_stmt* statement = nullptr; // The SQL statement

    // Compiles the SQL query into byte-code
    sqlite3_prepare(db, sqlQuery, -1, &statement, nullptr);

    // Moves the userInput's values into the SQL query
    sqlite3_bind_text(statement, 1, userInput.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 2, userInput.price);
    sqlite3_bind_text(statement, 3, userInput.entryDate.c_str(), -1, SQLITE_TRANSIENT);

    // Executes the query
    sqlite3_step(statement);

    sqlite3_finalize(statement);
}

// Read
const std::vector<SQLprocessor::Stock> SQLprocessor::crudRead(const Stock userInput) {
    const char* sqlQuery = "SELECT * FROM stocks WHERE "
                        "(id = ?1 OR ?1 = -1)AND "
                       "(name = ?2 OR ?2 = '') AND "
                       "(price = ?3 OR ?3 = -1.0) AND "
                        "(date = ?4 OR ?4 = '')";
    sqlite3_stmt* statement = nullptr;

    // Compiles the SQL query into byte-code
    sqlite3_prepare(db, sqlQuery, -1, &statement, nullptr);

    // Moves the userInput's values into the SQL query
    sqlite3_bind_int(statement, 1, userInput.id);
    sqlite3_bind_text(statement, 2, userInput.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 3, userInput.price);
    sqlite3_bind_text(statement, 4, userInput.entryDate.c_str(), -1, SQLITE_TRANSIENT);

    // Goes through each row returned by the SQL query and moves it into the stocks vector
    std::vector<SQLprocessor::Stock> stocks;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        Stock stock;

        stock.id = sqlite3_column_int(statement, 0);
        stock.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        stock.price = sqlite3_column_double(statement, 2);
        stock.entryDate = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));

        stocks.push_back(stock);
    }

    sqlite3_finalize(statement);

    return stocks;
}

// Update
void SQLprocessor::crudUpdate(const Stock userInput) {
    const char* sqlQuery = "UPDATE stocks SET "
                        "name = COALESCE(?1, name), "
                        "price = COALESCE(?2, price), "
                        "date = COALESCE(?3, date) "
                        "WHERE id = ?4";
    sqlite3_stmt* statement = nullptr;

    // Compiles the SQL query into byte-code
    sqlite3_prepare(db, sqlQuery, -1, &statement, nullptr);

    // Moves the userInput's values into the SQL query
    sqlite3_bind_text(statement, 1, userInput.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 2, userInput.price);
    sqlite3_bind_text(statement, 3, userInput.entryDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 4, userInput.id);

    // Executes the query
    sqlite3_step(statement);

    sqlite3_finalize(statement);
}

// Delete
void SQLprocessor::crudDelete(const Stock userInput) {

}
