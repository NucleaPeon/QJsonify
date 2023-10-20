#-------------------------------------------------
#
# Project created by QtCreator 2023-10-15T11:05:04
#
#-------------------------------------------------

QT       += core widgets printsupport

TARGET = QJsonify
TEMPLATE = app
ICON = qjsonify.icns

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

win32 {
    QT += winextras
}



FORMS    += mainwindow.ui\
        about.ui

RESOURCES += \
    main.qrc

OTHER_FILES += \
    LICENSE
