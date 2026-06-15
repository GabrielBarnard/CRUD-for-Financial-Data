/*
 * Made by Gabriel Barnard
 * Updated on the 15th of June 2026
 */

#include "../inc/SQLwindow.hpp"
#include <ui_SQLwindow.h>

#include <QStringListModel>
#include <QDate>

SQLwindow::SQLwindow(const std::string filePath, QWidget *parent) : QMainWindow(parent), ui(new Ui::SQLwindow), sqlProcessor(std::make_unique<SQLprocessor>(filePath)) {
    ui->setupUi(this);
    setWindowTitle("CRUD for Financial Data");
}

SQLwindow::~SQLwindow() {
    delete ui;
}

/*
 * fetchUserInput()
 * Fetches and validates user input from SQLwindow GUI
 * O(n) time complexity
 * O(1) space complexity
 */
SQLprocessor::Stock SQLwindow::fetchUserInput() {
    SQLprocessor::Stock stock;
    bool isUserInputInvalid{false};

    // Entry Date
    if (ui->dateEdit->text() != "" && !QDate::fromString(ui->dateEdit->text(), "yyyy-MM-dd").isValid())  {
        ui->dateEdit->setText("Invalid date");
        isUserInputInvalid = true;
    } else {
        stock.entryDate = ui->dateEdit->text().toStdString();
    }

    // Stock ID
    if (ui->idEdit->text().toStdString().empty()) {
        stock.id = -1;
    } else {
        try {
            stock.id = std::stoi(ui->idEdit->text().toStdString());
        } catch (...) {
            ui->idEdit->setText("Invalid Stock ID");
            isUserInputInvalid = true;
        }
    }

    // Stock Name
    stock.name = ui->nameEdit->text().toStdString();

    // Stock Price
    if (!ui->priceEdit->text().toStdString().empty()) {
        try {
            stock.price = std::stod(ui->priceEdit->text().toStdString());
        } catch (...) {
            ui->priceEdit->setText("Invalid Stock Price");
            isUserInputInvalid = true;
        }
    } else {
        stock.price = -1;
    }

    if (isUserInputInvalid) {
        throw std::runtime_error("A user Input field was invalid.");
    }

    return stock;
}

/*
 * on_createButton_clicked()
 * Creates a new stock entry
 */
void SQLwindow::on_createButton_clicked() {
    SQLprocessor::Stock userInputStock{};
    try {
        userInputStock = fetchUserInput();
    } catch (...) {
        return;
    }
    bool isUserInputInvalid{false};

    // Validates user input by checking if stock's name, price, or entry date is empty
    if (userInputStock.id != -1) {
        ui->idEdit->setText("ID not permitted");
        isUserInputInvalid = true;
    }
    if (userInputStock.name == "") {
        ui->nameEdit->setText("Name required");
        isUserInputInvalid = true;
    }
    if (userInputStock.price == -1) {
        ui->priceEdit->setText("Price required");
        isUserInputInvalid = true;
    }
    if (userInputStock.entryDate == "") {
        ui->dateEdit->setText("Date required");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }


    sqlProcessor->crudCreate(userInputStock);
}

/*
 * on_readButton_clicked()
 * Reads a specific or multiple stock entries
 */
void SQLwindow::on_readButton_clicked() {
    SQLprocessor::Stock userInputStock{};
    try {
        userInputStock = fetchUserInput();
    } catch (...) {
        return;
    }
    std::vector<SQLprocessor::Stock> stocks{};

    stocks = sqlProcessor->crudRead(userInputStock);

    // Move all stocks into QStringList
    QStringList stocksList{};
    for (const auto &stock : stocks) {
        // Add the stock to the Qt List
        // Formatting of this line has no impact on output, it's purely aesthetic
        stocksList << QString("Stock ID: %1 | Stock Name: %2 | Stock Price: %3 | Entry Date: %4")
                          .arg(stock.id)
                          .arg(QString::fromStdString(stock.name))
                          .arg(stock.price)
                          .arg(QString::fromStdString(stock.entryDate));
    }

    // Loads the listView with the Qt stocksList
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(stocksList);
    ui->listView->setModel(model);
}

/*
 * on_updateButton_clicked()
 * Updates a specific stock entry
 */
void SQLwindow::on_updateButton_clicked() {
    SQLprocessor::Stock userInputStock{};
    try {
        userInputStock = fetchUserInput();
    } catch (...) {
        return;
    }

    // Validates user input by ensuring id field is filled out
    if (userInputStock.id == -1) {
        ui->idEdit->setText("ID required");
        return;
    }

    sqlProcessor->crudUpdate(userInputStock);
}

/*
 * on_deleteButton_clicked()
 * Deletes a specific stock entry
 */
void SQLwindow::on_deleteButton_clicked() {
    SQLprocessor::Stock userInputStock{};
    try {
        userInputStock = fetchUserInput();
    } catch (...) {
        return;
    }

    // Validates user input by ensuring only the id field is filled out
    bool isUserInputInvalid{false};

    // Validates user input by checking if stock's name, price, or entry date is empty and if there is an input id
    if (userInputStock.id == -1) {
        ui->idEdit->setText("ID required");
        isUserInputInvalid = true;
    }
    if (userInputStock.name != "") {
        ui->nameEdit->setText("ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.price != -1) {
        ui->priceEdit->setText("ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.entryDate != "") {
        ui->dateEdit->setText("ID only");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }

    sqlProcessor->crudDelete(userInputStock);
}