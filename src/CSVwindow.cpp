/*
 * Made by Gabriel Barnard
 * Updated on the 31st of May 2026
 */

#include "../inc/CSVwindow.hpp"
#include <ui_CSVwindow.h>

#include <QStringListModel>

#include <cstdlib>
#include <sstream>
#include <iomanip>

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

// TODO: Validate user input in this function
CSVprocessor::Stock CSVwindow::fetchUserInput() {
    CSVprocessor::Stock stock;

    // Entry Date
    if  (!ui->lineEdit->text().toStdString().empty()) {
        struct std::tm tm{};
        std::istringstream ss(ui->lineEdit->text().toStdString());
        ss >> std::get_time(&tm, "%Y-%m-%d");

        if (ss.fail()) {
            ui->lineEdit->setText("Format: 1970-01-01");
            return CSVprocessor::Stock{};
        }

        stock.entryDate = std::mktime(&tm);
    } else {
        stock.entryDate = time_t{};
    }

    // Stock ID
    if (ui->lineEdit_2->text().toStdString().empty()) {
        stock.id = -1;
    } else {
        try {
            stock.id = std::stoi(ui->lineEdit_2->text().toStdString());
        } catch (...) {
            ui->lineEdit_2->setText("Invalid Stock ID");
        }
    }

    // Stock Name
    stock.name = ui->lineEdit_3->text().toStdString();

    // Stock Price
    if (!ui->lineEdit_4->text().toStdString().empty()) {
        stock.price = std::stoi(ui->lineEdit_4->text().toStdString());
    } else {
        stock.price = -1;
    }

    return stock;
}

// Create
void CSVwindow::on_pushButton_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};
    bool isUserInputInvalid{false};

    // Validates user input by checking if stock's name, price, or entry date is empty
    if (userInputStock.id != -1) {
        ui->lineEdit_2->setText("ID not permitted");
    }
    if (userInputStock.name == "") {
        ui->lineEdit_3->setText("Name required");
        isUserInputInvalid = true;
    }
    if (userInputStock.price == -1) {
        ui->lineEdit_4->setText("Price required");
        isUserInputInvalid = true;
    }
    if (userInputStock.entryDate == time_t{}) {
        ui->lineEdit->setText("Date required");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }

    csvProcessor->crudCreate(userInputStock);
}

// Read
void CSVwindow::on_pushButton_2_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};
    std::vector<CSVprocessor::Stock> stocks{};
    bool isUserInputInvalid{false};

    // Validate user input.
    if (userInputStock.name != "") {
        ui->lineEdit_3->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.price != -1) {
        ui->lineEdit_4->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.entryDate != time_t{}) {
        ui->lineEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }

    try {
        stocks = csvProcessor->crudRead(userInputStock);
    } catch (...) {
        ui->lineEdit_2->setText("Invalid Stock ID");
        return;
    }

    // Move all stocks into QStringList
    QStringList stocksList{};
    for (const auto &stock : stocks) {
        // Converts stock.entryDate to a string
        struct std::tm* tm{std::localtime(&stock.entryDate)};

        std::ostringstream ss{};
        ss << std::put_time(tm, "%Y-%m-%d");

        if (ss.fail()) {
            throw std::runtime_error("An error occured when translating time_t stock.entryDate to String in on_pushButton2_clicked()");
        }

        std::string date = ss.str();

        // Add the stock to the Qt List
        // Formatting of this line has no impact on output, it's purely aesthetic
        stocksList << QString("Stock ID: %1 | Stock Name: %2 | Stock Price: %3 | Entry Date: %4")
                          .arg(stock.id)
                          .arg(QString::fromStdString(stock.name))
                          .arg(stock.price)
                          .arg(QString::fromStdString(date));
    }

    // Loads the listView with the Qt stocksList
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(stocksList);
    ui->listView->setModel(model);
}

// Update
void CSVwindow::on_pushButton_3_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};

    try {
        csvProcessor->crudUpdate(userInputStock);
    } catch (...) {
        ui->lineEdit_2->setText("Invalid Stock ID");
        return;
    }
}

// Delete
void CSVwindow::on_pushButton_4_clicked() {
    CSVprocessor::Stock userInputStock{fetchUserInput()};
    bool isUserInputInvalid{false};

    // Validate user input.
    if (userInputStock.name != "") {
        ui->lineEdit_3->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.price != -1) {
        ui->lineEdit_4->setText("Stock ID only");
        isUserInputInvalid = true;
    }
    if (userInputStock.entryDate != time_t{}) {
        ui->lineEdit->setText("Stock ID only");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }

    try {
        csvProcessor->crudDelete(userInputStock);
    } catch (...) {
        ui->lineEdit_2->setText("Invalid Stock ID");
        return;
    }
}