/*
 * Made by Gabriel Barnard
 * Updated on the 15th of June 2026
 */

#include "../inc/CSVwindow.hpp"
#include <ui_CSVwindow.h>

#include <QStringListModel>

#include <cstdlib>
#include <QDate>

CSVwindow::CSVwindow(const std::string filePath, QWidget *parent) : QMainWindow(parent), ui(new Ui::CSVwindow), csvProcessor(std::make_unique<CSVprocessor>(filePath)) {
    ui->setupUi(this);
    setWindowTitle("CRUD for Financial Data");
}

CSVwindow::~CSVwindow() {
    delete ui;
}

// Handles closing the window
void CSVwindow::closeEvent(QCloseEvent *event) {
    // csvProcessor->close() cannot be called in a destructor, so I need to call it here
    csvProcessor->close();
    event->accept();
}

CSVprocessor::Stock CSVwindow::fetchUserInput() {
    CSVprocessor::Stock stock;

    // Entry Date
    if (ui->dateEdit->text() != "" && !QDate::fromString(ui->dateEdit->text(), "yyyy-MM-dd").isValid())  {
        ui->dateEdit->setText("Invalid date");
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
        }
    } else {
        stock.price = -1;
    }

    return stock;
}

// Create
void CSVwindow::on_createButton_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};
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

    csvProcessor->crudCreate(userInputStock);
}

// Read
void CSVwindow::on_readButton_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};
    std::vector<CSVprocessor::Stock> stocks{};
    bool isUserInputInvalid{false};

    // Validate user input.
    if (userInputStock.name != "") {
        ui->nameEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.price != -1) {
        ui->priceEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.entryDate != "") {
        ui->dateEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }

    try {
        stocks = csvProcessor->crudRead(userInputStock);
    } catch (...) {
        ui->idEdit->setText("Invalid Stock ID");
        return;
    }

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

// Update
void CSVwindow::on_updateButton_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};

    try {
        csvProcessor->crudUpdate(userInputStock);
    } catch (...) {
        ui->idEdit->setText("Invalid Stock ID");
        return;
    }
}

// Delete
void CSVwindow::on_deleteButton_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};
    bool isUserInputInvalid{false};

    // Validate user input.
    if (userInputStock.name != "") {
        ui->nameEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.price != -1) {
        ui->priceEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.entryDate != "") {
        ui->dateEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }

    try {
        csvProcessor->crudDelete(userInputStock);
    } catch (...) {
        ui->idEdit->setText("Invalid Stock ID");
        return;
    }
}