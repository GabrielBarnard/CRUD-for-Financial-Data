/*
 * Made by Gabriel Barnard
 * Updated on the 9th of June 2026
 */

#include <QFile>

#include "../inc/FileSelectionWindow.hpp"
#include <ui_FileSelectionWindow.h>

#include "../inc/CSVwindow.hpp"
#include "../inc/SQLwindow.hpp"

FileSelectionWindow::FileSelectionWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::FileSelectionWindow) {
    ui->setupUi(this);
    setWindowTitle("CRUD for Financial Data");
}

FileSelectionWindow::~FileSelectionWindow() {
    delete ui;
}

void FileSelectionWindow::on_pushButton_clicked() {
    QString filePath = ui->lineEdit->text();

    if (filePath.endsWith(".csv", Qt::CaseInsensitive) && QFile::exists(filePath)) {
        // Creates a new CSVwindow
        CSVwindow *csvWindow = new CSVwindow(filePath.toStdString());
        csvWindow->setWindowIcon(QIcon(":/appIcon.ico"));
        csvWindow->setStyleSheet("CSVwindow {background-color:#0e0e10;}"); // Makes the background a kind of black
        csvWindow->show();
        this->close();
    } else if (filePath.endsWith(".db", Qt::CaseInsensitive)) {
        try {
            // Creates a new SQLwindow
            SQLwindow *sqlWindow = new SQLwindow(filePath.toStdString());
            sqlWindow->setWindowIcon(QIcon(":/appIcon.ico"));
            sqlWindow->setStyleSheet("SQLwindow {background-color:#0e0e10;}"); // Makes the background a kind of black
            sqlWindow->show();
            this->close();
        } catch (...) {
            ui->lineEdit->setText("This .db file is invalid.");
        }
    } else if (!QFile::exists(filePath)) {
        ui->lineEdit->setText("This file does not exist");
    } else {
        ui->lineEdit->setText("Input invalid. Your input must be an existing .csv or .db file");
    }
}

