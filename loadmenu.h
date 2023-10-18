#ifndef LOADMENU_H
#define LOADMENU_H

#include <QMetaMethod>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#ifdef Q_OS_MAC
#include <QMacToolBar>
#include <QMacToolBarItem>
#endif

/*!
 * \brief The LoadMenu class is a file spec loader for menu setup.
 *
 * Unlike sbs and sbp files, this is internal only and handles consistency and
 * convenience by using a .json file that defines how a menu is configured so
 * it can be reproduced on all operating systems in similar fashion.
 * OS X = QMacToolBar
 * Win7+ = QWinThumbnailToolBar
 * Linux and WinXP = QToolBar
 *
 *
 * Once a defined spec file is read in, it is cached so menus can be generated repeatedly
 * without having to re-read the file.
 */

class LoadMenu
{
public:
    LoadMenu();

    static bool loadFile();
    static void setupToolBarOn(QWidget *widget = 0, QObject *slotobj = 0);


    static void setupMenus(QWidget *widget);
    static void setupWindowsToolBar(QWidget *widget, QObject *slotobj);
    static void setupNixToolBar(QWidget *widget, QObject *slotobj);
#ifdef Q_OS_MAC
    static void setupOSXToolBar(QWidget *widget, QObject *slotobj);
#endif

private:
    static void handleSignalSlot(QObject *connector, const char *signal, QObject *caller, const char *slot);
};

static bool slideEditorMenuLoaded;
static QJsonDocument slideEditorMenuDoc;

#endif // LOADMENU_H
