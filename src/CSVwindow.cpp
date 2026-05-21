/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#include "../inc/CSVwindow.hpp"
#include <ui_CSVwindow.h>

CSVwindow::CSVwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CSVwindow) {
    ui->setupUi(this);
    setWindowTitle("CRUD for Financial Data");
}

CSVwindow::~CSVwindow() {
    delete ui;
}
