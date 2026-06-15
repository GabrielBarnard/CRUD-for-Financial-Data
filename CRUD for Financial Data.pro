# Made by Gabriel Barnard
# Updated on the 15th of June 2026

QT += widgets
CONFIG += c++17 gui

# If on Linux, loads sqlite3 library from the device
# and sets the destdir to the bin/linux folder
unix {
        LIBS += -lsqlite3
        DESTDIR = $$PWD/bin/Linux
}

# If on Windows, loads the sqlite3 library from the win32 folder
# and sets the DESTDIR to the bin/windows folder
win32 {
        SOURCES += win32/sqlite3.c
        HEADERS += win32/sqlite3.h
        DESTDIR = $$PWD/bin/Windows
}

HEADERS += \
        inc/FileSelectionWindow.hpp \
        inc/CSVwindow.hpp \
        inc/SQLwindow.hpp \
        inc/CSVprocessor.hpp \
        inc/SQLprocessor.hpp
SOURCES += \
        src/main.cpp \
        src/FileSelectionWindow.cpp \
        src/CSVwindow.cpp \
        src/SQLwindow.cpp \
        src/CSVprocessor.cpp \
        src/SQLprocessor.cpp
FORMS += \
        ui/FileSelectionWindow.ui \
        ui/CSVwindow.ui \
        ui/SQLwindow.ui
RESOURCES += res/res.qrc
