#include <QApplication>
#include <QWidget>
#include <QIcon>

#include "../inc/GUImanager.hpp"

#include "../inc/FileSelectionWindow.hpp"

int GUImanager::enableGUI(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FileSelectionWindow window;
    window.setWindowIcon(QIcon(":/appIcon.ico"));
    window.show();

    return app.exec();
}
