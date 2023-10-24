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
#include <QPrinter>
#include <QPrintDialog>
#include <QtPrintSupport>
#include <QFileInfo>

#include "about.h"
#include "lib/qmenugen/loadmenu.h"

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
    void openAbout();
    void openPrintDialog(const QString outputName = "output.pdf");
    void minifyJson();
    void prettifyJson();
    void exportJson();

private:
    Ui::MainWindow *ui;
    QAction *aboutAction;
    QAction *preferencesAction;
    QAction *fileOpen;
    About *aboutWindow;
    QStatusBar *statusBar;

    void loadInputFile(QUrl input);
    void exportFile(QUrl output);

    QUrl openedUrl;
    QUrl defaultLocation;

};

#endif // MAINWINDOW_H
