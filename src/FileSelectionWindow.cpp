/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
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
        CSVwindow *csvWindow = new CSVwindow();
        csvWindow->setWindowIcon(QIcon(":/appIcon.ico"));
        csvWindow->show();
        this->close();
    } else if (filePath.endsWith(".db", Qt::CaseInsensitive)) {
        SQLwindow *sqlWindow = new SQLwindow();
        sqlWindow->setWindowIcon(QIcon(":/appIcon.ico"));
        sqlWindow->show();
        this->close();
    } else if (!QFile::exists(filePath)) {
        ui->lineEdit->setText("This file does not exist");
    } else {
        ui->lineEdit->setText("Input invalid. Your input must be an existing .csv or .db file");
    }
}

