/*
 * Made by Gabriel Barnard
 * Updated on the 15th of June 2026
 */

// No time or space complexity analysis because all notable operations are handled by SQLite

#include "../inc/SQLprocessor.hpp"

#include <stdexcept>

SQLprocessor::SQLprocessor (const std::string filePath) {
    if (sqlite3_open(filePath.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Unable to open SQLite3 database.");
    }

    // SQLite .db File Validation
    // First query - validates if there is a table called "stocks"
    {
    const char* sqlQuery = "SELECT name FROM sqlite_master WHERE type='table' AND name = 'stocks'";
    sqlite3_stmt* statement = nullptr; // The SQL statement

    // Compiles the SQL query into byte-code
    sqlite3_prepare(db, sqlQuery, -1, &statement, nullptr);

    // Executes the query
    // sqlite3_STEP returns SQLITE_ROW if the query is successful, SQLITE_DONE if it isn't
    if (sqlite3_step(statement) == SQLITE_DONE) {
        sqlite3_finalize(statement);
        throw std::runtime_error("The table \"stocks\" does not exist");
    }

    sqlite3_finalize(statement);
    }

    // Second and final query - validates if the table contains "id", "name", "price", and "date"
    {
    const char* sqlQuery = "SELECT COUNT(*) FROM pragma_table_info('stocks') WHERE "
                           "name IN ('id', 'name', 'price', 'date')";
    sqlite3_stmt* statement = nullptr; // The SQL statement

    // Compiles the SQL query into byte-code
    sqlite3_prepare(db, sqlQuery, -1, &statement, nullptr);

    // Executes the query
    sqlite3_step(statement);

    int columnCount{sqlite3_column_int(statement, 0)}; // Reads the result of the query

    sqlite3_finalize(statement);

    if (columnCount != 4) {
        throw std::runtime_error("Error. One of the following fields is not present in the .db file: \"id\", \"name\", \"price\", \"date\"");
    }
    }
}

SQLprocessor::~SQLprocessor (void) {
    sqlite3_close(db);
}

/*
 * crudCreate()
 * Adds a specific stock entry to the .db file
 */
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

/*
 * crudRead()
 * Reads a specific or multiple entries from the .db file, returning a vector
 */
const std::vector<SQLprocessor::Stock> SQLprocessor::crudRead(const Stock userInput) {
    const char* sqlQuery = "SELECT * FROM stocks WHERE "
                        "(id = ?1 OR ?1 = -1)AND "
                       "(name = ?2 OR ?2 = '') AND "
                       "(price = ?3 OR ?3 = -1.0) AND "
                        "(date = ?4 OR ?4 = '')";
    sqlite3_stmt* statement = nullptr; // The SQL statement

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

/*
 * crudUpdate()
 * Updates a specific entry in the .db file
 */
void SQLprocessor::crudUpdate(const Stock userInput) {
    const char* sqlQuery = "UPDATE stocks SET "
                        "name = COALESCE(?1, name), "
                        "price = COALESCE(?2, price), "
                        "date = COALESCE(?3, date) "
                        "WHERE id = ?4";
    sqlite3_stmt* statement = nullptr; // The SQL statement

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

/*
 * crudDelete()
 * Deletes a specific entry from the .db file
 */
void SQLprocessor::crudDelete(const Stock userInput) {
    const char* sqlQuery = "DELETE FROM stocks WHERE id = ?1";
    sqlite3_stmt* statement = nullptr; // The SQL statement

    // Compiles the SQL query into byte-code
    sqlite3_prepare(db, sqlQuery, -1, &statement, nullptr);

    // Moves the userInput's values into the SQL query
    sqlite3_bind_int(statement, 1, userInput.id);

    // Executes the query
    sqlite3_step(statement);

    sqlite3_finalize(statement);
}
