/*
 * Made by Gabriel Barnard
 * Updated on the 15th of June 2026
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
        void on_createButton_clicked();
        void on_readButton_clicked();
        void on_updateButton_clicked();
        void on_deleteButton_clicked();
    private:
        Ui::SQLwindow *ui;

        std::unique_ptr<SQLprocessor> sqlProcessor;

        SQLprocessor::Stock fetchUserInput();
};
