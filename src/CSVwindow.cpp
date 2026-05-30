/*
 * Made by Gabriel Barnard
 * Updated on the 29th of May 2026
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

// TODO: Validate user input in this function
CSVprocessor::Stock CSVwindow::fetchUserInput() {
    CSVprocessor::Stock stock;

    // Entry Date
    if  (!ui->lineEdit->text().toStdString().empty()) {
        struct std::tm tm{};
        std::istringstream ss(ui->lineEdit->text().toStdString());
        ss >> std::get_time(&tm, "%Y-%m-%d");

        if (ss.fail()) {
            ui->lineEdit->setText("Incorrect Format. Must be 1970-01-01");
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
        } catch (const std::exception) {
            ui->lineEdit->setText("ID may only contain numbers and must be 0 or greater.");
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

// Read
void CSVwindow::on_pushButton_2_clicked() {
    std::vector<CSVprocessor::Stock> stocks {csvProcessor->crudRead(fetchUserInput())};

    QStringList stocksList{};
    for (const auto &stock : stocks) {
        // Converts the stock's date to a string
        struct std::tm* tm{std::gmtime(&stock.entryDate)}; // Uses UTC (Greenwich Mean Time)

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
// void CSVwindow::on_pushButton_3_clicked() {}

// Delete
void CSVwindow::on_pushButton_4_clicked() {
    csvProcessor->crudDelete(fetchUserInput());
}