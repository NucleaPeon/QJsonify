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
	
	# For easy results, use qtcreator. Don't try doing this on the command line unless you know what you are doing.
	
    # You may need to change this path to your installed DDK/Microsoft Windows SDK as well as 32/64 bit
    #INCLUDEPATH += "C:/WinDDK/7600.16385.1/inc/crt" \
    #    "C:/WinDDK/7600.16385.1/inc/api" \
	#	"C:/Program Files (x86)/Microsoft Visual Studio 12.0/VC/include/utility" \
	#	"C:/Program Files (x86)/Microsoft Visual Studio 12.0/VC/include/cliext/utility"

    #LIBS += -L"C:/WinDDK/7600.16385.1/lib/Crt/i386"
}



FORMS    += mainwindow.ui\
        about.ui

RESOURCES += \
    main.qrc

OTHER_FILES += \
    LICENSE \
    menu_defs.json
