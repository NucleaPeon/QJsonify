#include "loadmenu.h"
#include <QDebug>

LoadMenu::LoadMenu()
{
}

bool LoadMenu::loadFile()
{
    QFile file(":/filespecs/menu_defs.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonParseError err;
        slideEditorMenuDoc = QJsonDocument::fromJson(file.readAll(), &err);
        if(err.error != QJsonParseError::NoError) {
            QString msg = QString("Unable to parse slide menu json file (%1)").arg(err.errorString());
            qWarning(msg.toLatin1());
        }
        file.close();
    } else {
        slideEditorMenuLoaded = false;
        return slideEditorMenuLoaded;
    }
    slideEditorMenuLoaded = true;
    return slideEditorMenuLoaded;
}

void LoadMenu::setupToolBarOn(QWidget *widget, QObject *slotobj)
{
    qDebug() << widget;
    if (slideEditorMenuLoaded == false)
        LoadMenu::loadFile();

    setupMenus(widget);
#ifdef Q_OS_MAC
    setupOSXToolBar(widget, slotobj);
#endif
}

void LoadMenu::setupMenus(QWidget *widget)
{
    QMenuBar *mb = new QMenuBar(widget);
    QJsonArray arr = slideEditorMenuDoc.array();
    foreach(QJsonValue val, arr) {
        QJsonObject obj = val.toObject();
        QMenu *m = new QMenu(obj.value("name").toString(""));
        foreach(QJsonValue actval, obj.value("actions").toArray()) {
            QJsonObject actobj = actval.toObject();
            if (actobj.contains("separator")) {
                m->addSeparator();
                continue;
            }
            bool has_checked = actobj.contains("checked");
            if (actobj.value("visible_on_mac").toString("true") == "true") {
                const QIcon icon = QIcon(actobj.value("icon").toString());
                QAction *act = new QAction(icon, actobj.value("text").toString(), m->parent());
                if (has_checked) {
                    act->setCheckable(true);
                    act->setChecked(bool(actobj.value("checked").toString()=="true"));
                }
                m->addAction(act);
                if (actobj.contains("slot")) {
                    QString slot = actobj.value("slot").toString();
                    LoadMenu::handleSignalSlot(act, "triggered()", widget, slot.toLocal8Bit().data());
                }
            }
        }

        mb->addMenu(m);
    }
}

void LoadMenu::setupWindowsToolBar(QWidget *widget, QObject *slotobj)
{
    QJsonArray arr = slideEditorMenuDoc.array();
    foreach(QJsonValue val, arr) {
        qWarning("TODO: Windows Ribbon Toolbar");
    }
}

void LoadMenu::setupNixToolBar(QWidget *widget, QObject *slotobj)
{
    QJsonArray arr = slideEditorMenuDoc.array();
    foreach(QJsonValue val, arr) {
        qWarning("TODO: Nix Tool Bar");
    }
}
#ifdef Q_OS_MAC
void LoadMenu::setupOSXToolBar(QWidget *widget, QObject *slotobj)
{
    QJsonArray arr = slideEditorMenuDoc.array();
    QMacToolBar *tb = new QMacToolBar();
    foreach(QJsonValue val, arr) {
        QJsonObject obj = val.toObject();
        foreach(QJsonValue actval, obj.value("actions").toArray()) {
            QJsonObject actobj = actval.toObject();
            // Allow hiding of separators on toolbars (but not menus), set toolbar_hidden.
            bool toolbar_hidden = actobj.value("toolbar_hidden").toString("false") == "true";
            if (actobj.contains("separator") && ! toolbar_hidden) {
                tb->addSeparator();
                continue;
            }

            const QIcon icon = QIcon(actobj.value("icon").toString());
            const QString name = actobj.value("text").toString().remove('&');
            QMacToolBarItem *tbitem;
            if (toolbar_hidden) {
                tbitem = tb->addAllowedItem(icon, name);
            } else {
                tbitem = tb->addItem(icon, name);
            }
            if (actobj.contains("slot")) {
                QString slot = actobj.value("slot").toString();
                LoadMenu::handleSignalSlot(tbitem, "activated()", widget, slot.toLocal8Bit().data());
            }
        }
    }
    tb->attachToWindow(widget->windowHandle());
}

#endif

void LoadMenu::handleSignalSlot(QObject *connector, const char *signal, QObject *caller, const char *slot)
{
    const QMetaObject *metaConn = connector->metaObject();
    int sigIdx = metaConn->indexOfSignal(signal);
    qDebug() << signal;
    if (sigIdx < 0) { qWarning("Menu/Toolbar signal method not found"); return; }
    const QMetaMethod sigMethod = metaConn->method(sigIdx);

    const QMetaObject *metaCall = caller->metaObject();
    int slotIdx = metaCall->indexOfSlot(slot);
    qDebug() << slot;
    if (sigIdx < 0) { qWarning("Menu/Toolbar slot method not found"); return; }
    const QMetaMethod slotMethod = metaCall->method(slotIdx);

    QObject::connect(connector, sigMethod, caller, slotMethod);
}
