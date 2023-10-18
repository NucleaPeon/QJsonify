#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QAction>
#include <QUrl>
#include <QFileDialog>
#include <QFlags>
#include <QDir>
#include <QFile>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "about.h"
#include "preferences.h"
#include "loadmenu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openUrl();

private:
    Ui::MainWindow *ui;
    QAction *aboutAction;
    QAction *preferencesAction;
    QAction *fileOpen;
    About *aboutWindow;
    Preferences *preferencesWindow;
    QStatusBar *statusBar;

    void loadInputFile(QUrl input);

    QUrl *openedFile;
    QUrl *defaultLocation;

};

#endif // MAINWINDOW_H
