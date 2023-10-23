#include "loadmenu.h"

LoadMenu::LoadMenu()
{
}

bool LoadMenu::loadFile(QUrl url)
{
    QFile file(url.path());
    if (! file.exists())
        return false;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonParseError err;
        _json = QJsonDocument::fromJson(file.readAll(), &err);
        if(err.error != QJsonParseError::NoError) {
            QString msg = QString("Unable to parse slide menu json file (%1)").arg(err.errorString());
            qWarning(msg.toLatin1());
        }
        file.close();
    } else {
        _loaded = false;
        return _loaded;
    }
    _loaded = true;
    return _loaded;
}

void LoadMenu::setupToolBarOn(QUrl definition, QWidget *widget, QObject *slotobj)
{
    _action_map = QMap<QString, QAction*>();
    if (_loaded == false)
        LoadMenu::loadFile(definition);

    mb = setupMenus(widget);
#ifdef Q_OS_MAC
    tb = setupOSXToolBar(widget, slotobj);
#endif
#ifdef Q_OS_LINUX
    tb = setupNixToolBar(widget, slotobj);
#endif
}

void LoadMenu::setupToolBarOn(QUrl definition, QMainWindow *window, QObject *slotobj)
{
    _action_map = QMap<QString, QAction*>();
    if (_loaded == false)
        LoadMenu::loadFile(definition);

   mb = setupMenus(window);
   window->setMenuBar(mb);
#ifdef Q_OS_MAC
    tb = setupOSXToolBar(window, slotobj);
#endif
#ifdef Q_OS_LINUX
    tb = setupNixToolBar(window, slotobj);
    window->addToolBar(tb);
#endif
}

QAction *LoadMenu::actionByName(const QString name)
{
    return _action_map.value(name, NULL);
}

QMenuBar* LoadMenu::setupMenus(QWidget *widget)
{
    QMenuBar *mb = new QMenuBar(widget);
    QJsonArray arr = _json.array();
    foreach(QJsonValue val, arr) {
        QJsonObject obj = val.toObject();
        QMenu *m = new QMenu(obj.value("name").toString(""));
        foreach(QJsonValue actval, obj.value("actions").toArray()) {
            QJsonObject actobj = actval.toObject();
            if (actobj.contains("separator")) {
                m->addSeparator();
                continue;
            }
            const bool has_checked = actobj.contains("checked");
            const QIcon icon = QIcon(actobj.value("icon").toString());
            QAction *act = new QAction(icon, actobj.value("text").toString(), m->parent());
            act->setData(QVariant(actobj.value("name")));

            if (has_checked) {
                act->setChecked(actobj.value("checked").toBool());
            }
            const QString sc = QObject::tr(actobj.value("shortcut").toString().toLatin1().data());
            if (! sc.isNull() && ! sc.isEmpty()) {
                act->setShortcut(QKeySequence::fromString(sc));
            }
            act->setEnabled(actobj.value("enabled").toBool(true));
            m->addAction(act);
            if (actobj.contains("slot")) {
                QString slot = actobj.value("slot").toString();
                LoadMenu::handleSignalSlot(act, "triggered()", widget, slot.toLocal8Bit().data());
            }
            _action_map[actobj.value("name").toString()] = act;

        }

        mb->addMenu(m);
    }
    return mb;
}
#ifdef Q_OS_WIN
QWinThumbnailToolBar* LoadMenu::setupWindowsToolBar(QWidget *widget, QObject *slotobj)
{
    QJsonArray arr = _json.array();
    foreach(QJsonValue val, arr) {
        qWarning("TODO: Windows Ribbon Toolbar");
    }
}
#endif
#ifdef Q_OS_LINUX
QToolBar* LoadMenu::setupNixToolBar(QWidget *widget, QObject *slotobj)
{
    QJsonArray arr = _json.array();
    QToolBar *tb = new QToolBar(widget);

    foreach(QJsonValue val, arr) {
        // QActions already set up and configured
        QJsonObject obj = val.toObject();
        foreach(QJsonValue actval, obj.value("actions").toArray()) {
            QJsonObject actobj = actval.toObject();
            bool toolbar_hidden = actobj.value("toolbar_hidden").toBool(false);
            if (actobj.contains("separator") && ! toolbar_hidden) {
                tb->addSeparator();
                continue;
            }
            const QString name = actobj.value("name").toString();
            QAction *act = _action_map.value(name, NULL);
            if (act != NULL) {
                // Just don't add. As long as OS X is working, or until we impl our own toolbar visibility ui widget,
                // they can use the menus.
                if (toolbar_hidden) { continue; }
                tb->addAction(act);
            }

        }
    }
    return tb;
}
#endif

#ifdef Q_OS_MAC
QMacToolBar* LoadMenu::setupOSXToolBar(QWidget *widget, QObject *slotobj)
{
    QJsonArray arr = _json.array();
    QMacToolBar *tb = new QMacToolBar();
    foreach(QJsonValue val, arr) {
        QJsonObject obj = val.toObject();
        foreach(QJsonValue actval, obj.value("actions").toArray()) {
            QJsonObject actobj = actval.toObject();
            // Allow hiding of separators on toolbars (but not menus), set toolbar_hidden.
            bool toolbar_hidden = actobj.value("toolbar_hidden").toBool(false);
            if (actobj.contains("separator") && ! toolbar_hidden) {
                tb->addSeparator();
                continue;
            }
            const bool enabled = actobj.value("enabled").toBool(true);
            QIcon icon = QIcon(actobj.value("icon").toString());
            // FIXME: enabled currently doesn't work on QMacToolBarItem
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
    return tb;
}

QMacToolBarItem *LoadMenu::toolBarItemByText(QString text)
{
    const QString name = text.remove('&');
    foreach(QMacToolBarItem* item, tb->items()) {
        if (item->text() == name)
            return item;
    }
    return NULL;
}

#endif

void LoadMenu::handleSignalSlot(QObject *connector, const char *signal, QObject *caller, const char *slot)
{
    const QMetaObject *metaConn = connector->metaObject();
    int sigIdx = metaConn->indexOfSignal(signal);
    if (sigIdx < 0) { qWarning("Menu/Toolbar signal method not found"); return; }
    const QMetaMethod sigMethod = metaConn->method(sigIdx);

    const QMetaObject *metaCall = caller->metaObject();
    int slotIdx = metaCall->indexOfSlot(slot);
    if (sigIdx < 0) { qWarning("Menu/Toolbar slot method not found"); return; }
    const QMetaMethod slotMethod = metaCall->method(slotIdx);

    QObject::connect(connector, sigMethod, caller, slotMethod);
}
