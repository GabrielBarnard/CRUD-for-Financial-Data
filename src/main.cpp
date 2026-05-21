/*
 * Made by Gabriel Barnard
 * Made on the 21st of May 2026
 */

#include "../inc/FileSelectionWindow.hpp"

#include <QApplication>

#include <cstdlib>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FileSelectionWindow window;
    window.setWindowIcon(QIcon(":/appIcon.ico"));
    window.show();

    return app.exec();
}
