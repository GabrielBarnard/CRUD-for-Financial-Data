/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#pragma once

#include <QMainWindow>

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
private:
    Ui::CSVwindow *ui;
};
