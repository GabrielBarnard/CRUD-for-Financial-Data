# Made by Gabriel Barnard
# Updated on the 2nd of June 2026

QT += widgets
CONFIG += c++17 gui

# If on Linux, loads sqlite3 library from the device
unix {
        LIBS += -lsqlite3
}

# if on Windows, loads the sqlite3 library from the win32 folder
win32 {
        SOURCES += win32/sqlite3.c
        HEADERS += win32/sqlite3.h
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

DESTDIR = $$PWD/bin # Creates the executable in the bin folder inside the root folder, rather than the build folder