#-------------------------------------------------
#
# Project created by QtCreator 2023-10-15T11:05:04
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QJsonify
TEMPLATE = app
ICON += $$PWD/icons/qjsonify.icns
QMAKE_INFO_PLIST = Info.plist

SOURCES += main.cpp\
        mainwindow.cpp\
        about.cpp\
        loadmenu.cpp

HEADERS  += mainwindow.h\
        about.h\
        loadmenu.h

macx { 

    LIBS += -framework Cocoa

    QT += macextras

    OBJECTIVE_SOURCES += cocoainitializer.mm
    OBJECTIVE_HEADERS += cocoainitializer.h

}


FORMS    += mainwindow.ui\
        about.ui

RESOURCES += \
    main.qrc
