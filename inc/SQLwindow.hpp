/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class SQLwindow;
}
QT_END_NAMESPACE

class SQLwindow : public QMainWindow {
    Q_OBJECT
public:
    explicit SQLwindow(QWidget *parent = nullptr);
    ~SQLwindow();
private:
    Ui::SQLwindow *ui;
};
