/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#include "../inc/SQLwindow.hpp"
#include <ui_SQLwindow.h>

SQLwindow::SQLwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SQLwindow) {
    ui->setupUi(this);
    setWindowTitle("CRUD for Financial Data");
}

SQLwindow::~SQLwindow() {
    delete ui;
}
