/*
 * Made by Gabriel Barnard
 * Updated on the 29th of May 2026
 */

#include "../inc/CSVprocessor.hpp"

#include "../inc/CSVwindow.hpp"
#include <ui_CSVwindow.h>

#include <memory>

CSVwindow::CSVwindow(const std::string filePath, QWidget *parent) : QMainWindow(parent), ui(new Ui::CSVwindow) {
    ui->setupUi(this);
    setWindowTitle("CRUD for Financial Data");
    auto csvProcessor = std::make_unique<CSVprocessor>(filePath);
}

CSVwindow::~CSVwindow() {
    delete ui;
}
