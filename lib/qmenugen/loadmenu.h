#ifndef LOADMENU_H
#define LOADMENU_H

#include <QMainWindow>
#include <QMetaMethod>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QUrl>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMap>

#ifdef Q_OS_MAC
#include <QMacToolBar>
#include <QMacToolBarItem>
#endif

#ifdef Q_OS_WIN
#include <QtWinExtras>
#include <QWinThumbnailToolBar>
#endif

#ifdef Q_OS_LINUX
#include <QToolBar>
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

    static bool loadFile(QUrl url);
    static void setupToolBarOn(QUrl definition, QWidget *widget = 0, QObject *slotobj = 0);
    static void setupToolBarOn(QUrl definition, QMainWindow *window = 0, QObject *slotobj = 0);

    /*!
     * \brief actionByName Retrieves a QAction based on name defined in the menu_defs.json
     * \param name QString
     * \return QAction* or NULL if not found
     */
    static QAction* actionByName(const QString name);

    static QMenuBar *setupMenus(QWidget *widget);
#ifdef Q_OS_WIN
    // UNTESTED
    static QWinThumbnailToolBar* setupWindowsToolBar(QWidget *widget, QObject *slotobj);
#endif
#ifdef Q_OS_LINUX
    static QToolBar* setupNixToolBar(QWidget *widget, QObject *slotobj);
#endif
#ifdef Q_OS_MAC
    static QMacToolBar* setupOSXToolBar(QWidget *widget, QObject *slotobj);
    static QMacToolBarItem* toolBarItemByText(QString text);
#else
    static QAction* toolBarItemByText(QString text);
#endif

private:
    static void handleSignalSlot(QObject *connector, const char *signal, QObject *caller, const char *slot);
};

static bool _loaded;
static QJsonDocument _json;
static QMap<QString, QAction*> _action_map;
static QMenuBar* mb;
#ifdef Q_OS_MAC
static QMacToolBar *tb;
#else
static QToolBar *tb;
#endif

#endif // LOADMENU_H
