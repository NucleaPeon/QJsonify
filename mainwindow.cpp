#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

/*!
 * TODO:
 *      [ ] Implement the multiplatform toolbar mechanism here:
 *          [ ] Recent files
 *          [ ] Open Print | Edit | Minify Prettify | Export
 *          [ ] On application focus, check if loaded file has been modified if local and reload it. To do so on remote requires setting option in preferences.
 *          [ ] QJsonParseError should show messages in status bar
 *          [ ] Impl help and preferences modals
 *          [ ] Create icons
 *          [ ] Build for OS X
 *          [ ] Use CMake instead of qmake
 *          [ ] Upload to github
 *          [ ] Debian package
 *          [ ] Should we use tabbed for multiple json file viewing?
 *          [ ] Should we have a comparison?
 *          [ ] Show filesize difference between pretty and mini.
 *          [ ] Either allow editing or an 'open in editor' option
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	this->aboutAction = new QAction(0);
    this->aboutAction->setMenuRole(QAction::AboutRole);
    this->aboutWindow = new About();
    this->preferencesAction = new QAction(0);
    this->preferencesAction->setMenuRole(QAction::PreferencesRole);
    this->preferencesWindow = new Preferences();
    ui->setupUi(this);
    this->defaultLocation = new QUrl(QDir::homePath());
    LoadMenu::setupToolBarOn(this, this);
    connect(this->aboutAction, SIGNAL(triggered()), this->aboutWindow, SLOT(show()));
    connect(this->preferencesAction, SIGNAL(triggered()), this->preferencesWindow, SLOT(show()));


    this->statusBar = new QStatusBar();
    this->setStatusBar(this->statusBar);
    this->statusBar->showMessage("Ready.");
}

MainWindow::~MainWindow()
{
	delete this->aboutAction;
    delete this->aboutWindow;
    delete this->preferencesAction;
    delete this->preferencesWindow;
    delete this->statusBar;
    delete ui;
}

void MainWindow::openUrl()
{
    QFileDialog *dia = new QFileDialog(0, "Open JSON File", this->defaultLocation->path(), "*.json");
    dia->setFileMode(QFileDialog::ExistingFile);
    QList<QUrl> urls;
    if (dia->exec())
        urls = dia->selectedUrls();
    loadInputFile(urls.at(0));
}

void MainWindow::loadInputFile(QUrl input)
{
    if (input.isLocalFile()) {
        QFile in(input.path());
        if (in.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(in.readAll(), &err);
            ui->textInput->setText(doc.toJson());
            if (err.error != QJsonParseError::NoError) {
                qWarning(err.errorString().toLatin1());
            }
        }
    } else {
        qDebug() << "TODO: Remote file reading";
    }

}
