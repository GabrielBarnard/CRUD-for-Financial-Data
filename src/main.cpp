/*
 * Made by Gabriel Barnard
 * Made on the 9th of May 2026
 */

#include "../inc/FileSelectionWindow.hpp"

#include <QApplication>

#include <cstdlib>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FileSelectionWindow window;
    window.setWindowIcon(QIcon(":/appIcon.ico"));
    window.setStyleSheet("FileSelectionWindow {background-color:#0e0e10;}"); // Makes the background a kind of black
    window.show();

    return app.exec();
}
