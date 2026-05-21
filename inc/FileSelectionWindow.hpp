/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class FileSelectionWindow;
}
QT_END_NAMESPACE

class FileSelectionWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit FileSelectionWindow(QWidget *parent = nullptr);
        ~FileSelectionWindow();
    private slots:
        void on_pushButton_clicked();

    private:
        Ui::FileSelectionWindow *ui;
};
