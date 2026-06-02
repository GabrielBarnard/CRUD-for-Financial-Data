/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#pragma once

#include "../inc/SQLprocessor.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class SQLwindow;
}
QT_END_NAMESPACE

class SQLwindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit SQLwindow(const std::string filePath, QWidget *parent = nullptr);
        ~SQLwindow();
    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();
        void on_pushButton_4_clicked();
    private:
        Ui::SQLwindow *ui;

        std::unique_ptr<SQLprocessor> sqlProcessor;

        SQLprocessor::Stock fetchUserInput();
};
