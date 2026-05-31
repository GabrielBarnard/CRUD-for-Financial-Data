/*
 * Made by Gabriel Barnard
 * Updated on the 31st of May 2026
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
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();
        void on_pushButton_4_clicked();
    private:
        Ui::CSVwindow *ui;

        std::unique_ptr<CSVprocessor> csvProcessor;

        CSVprocessor::Stock fetchUserInput();
    protected:
        void closeEvent(QCloseEvent *event);
};