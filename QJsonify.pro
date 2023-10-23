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
        lib/qmenugen/loadmenu.cpp

HEADERS  += mainwindow.h\
        about.h\
    lib/qmenugen/loadmenu.h

macx { 
    LIBS += -framework Cocoa

    QT += macextras

    OBJECTIVE_SOURCES += lib/cocoainitializer/cocoainitializer.mm
    OBJECTIVE_HEADERS += lib/cocoainitializer/cocoainitializer.h

}

win32 {
    QT += winextras
}



FORMS    += mainwindow.ui\
        about.ui

RESOURCES += \
    main.qrc

OTHER_FILES += \
    LICENSE \
    menu_defs.json
