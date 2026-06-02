/*
 * Made by Gabriel Barnard
 * Updated on the 2nd of June 2026
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

SQLprocessor::Stock SQLwindow::fetchUserInput() {
    SQLprocessor::Stock stock;

    // Entry Date
    if (QDate::fromString(ui->lineEdit->text(), "yyyy-MM-dd").isValid() || ui->lineEdit->text().toStdString() == "") {
        stock.entryDate = ui->lineEdit->text().toStdString();
    } else {
        ui->lineEdit->setText("Format: 1970-01-01");
        return SQLprocessor::Stock{};
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
void SQLwindow::on_pushButton_clicked() {
    SQLprocessor::Stock userInputStock{fetchUserInput()};
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
    if (userInputStock.entryDate == "") {
        ui->lineEdit->setText("Date required");
        isUserInputInvalid = true;
    }

    if (isUserInputInvalid) {
        return;
    }


    sqlProcessor->crudCreate(userInputStock);
}

// Read
void SQLwindow::on_pushButton_2_clicked() {
    SQLprocessor::Stock userInputStock{fetchUserInput()};
    std::vector<SQLprocessor::Stock> stocks{};

    if (userInputStock.id != -1 && userInputStock.id < 1) {
        ui->lineEdit_2->setText("Invalid Stock ID");
    }

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
