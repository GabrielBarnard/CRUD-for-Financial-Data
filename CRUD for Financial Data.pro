# Made by Gabriel Barnard
# Made on the 21st of May 2026

QT += widgets
CONFIG += c++17 gui

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

DESTDIR = $$PWD/bin # Creates the executable in the root folder, rather than the build folder