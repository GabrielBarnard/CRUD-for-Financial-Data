/*
 * Made by Gabriel Barnard
 * Updated on the 15th of June 2026
 */

#pragma once

#include "../inc/CSVprocessor.hpp"

#include <QMainWindow>
#include <QCloseEvent>

#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
    class CSVwindow;
}
QT_END_NAMESPACE

class CSVwindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit CSVwindow(const std::string filePath, QWidget *parent = nullptr);
        ~CSVwindow();
    private slots:
        void on_createButton_clicked();
        void on_readButton_clicked();
        void on_updateButton_clicked();
        void on_deleteButton_clicked();
    private:
        Ui::CSVwindow *ui;

        std::unique_ptr<CSVprocessor> csvProcessor;

        CSVprocessor::Stock fetchUserInput();
    protected:
        void closeEvent(QCloseEvent *event);
};