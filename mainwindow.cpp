#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>

/*!
 * TODO:
 *      [ ] Implement the multiplatform toolbar mechanism here:
 *          [ ] Recent files
 *          [ ] Remote loading and exporting of files
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
    ui->setupUi(this);
#if QT_VERSION > QT_VERSION_CHECK(5, 3, 3)
    ui->textInput->setTabStopDistance(ui->textInput->tabStopDistance()/2);
    ui->textOutput->setTabStopDistance(ui->textOutput->tabStopDistance()/2);
#else
    ui->textInput->setTabStopWidth(ui->textInput->tabStopWidth()/2);
    ui->textOutput->setTabStopWidth(ui->textOutput->tabStopWidth()/2);
#endif
    this->defaultLocation = QUrl(QDir::homePath());

    QFile def(":/filespecs/menu_defs.json");
    LoadMenu::setupToolBarOn(&def, this, this);
    connect(this->aboutAction, SIGNAL(triggered()), this->aboutWindow, SLOT(show()));

    this->statusBar = new QStatusBar();
    this->setStatusBar(this->statusBar);
    this->statusBar->showMessage("Ready.");
}

MainWindow::~MainWindow()
{
	delete this->aboutAction;
    delete this->aboutWindow;
    delete this->statusBar;
    delete ui;
}

void MainWindow::openUrl()
{
    QFileDialog *dia = new QFileDialog(0, "Open JSON File", this->defaultLocation.path(), "*.json");
    dia->setFileMode(QFileDialog::ExistingFile);
    QList<QUrl> urls;
    if (dia->exec())
        urls = dia->selectedUrls();
    if (urls.isEmpty())
        return;

    loadInputFile(urls.at(0));
}

void MainWindow::openAbout()
{
    this->aboutWindow->show();
}

void MainWindow::openPrintDialog(const QString outputName)
{
    if (ui->textInput->document()->characterCount() < 2)
        return;

    QPrintDialog printDialog;
    if (printDialog.exec() == QDialog::Accepted) {
        QPrinter *printer = printDialog.printer();
        // printer->setResolution(QPrinter::HighResolution);
        // printer->setColorMode(QPrinter::GrayScale);
        // printer->setOutputFormat(QPrinter::NativeFormat);
        //printer->setOutputFileName(outputName);
        ui->textOutput->document()->print(printer);
        //printDialog.done(QDialog::Accepted);
    }
}

void MainWindow::minifyJson()
{
    QJsonDocument doc = QJsonDocument::fromJson(ui->textInput->toPlainText().toUtf8());
    ui->textOutput->setText(doc.toJson(QJsonDocument::Compact));
}

void MainWindow::prettifyJson()
{
    QJsonDocument doc = QJsonDocument::fromJson(ui->textInput->toPlainText().toUtf8());
    ui->textOutput->setText(doc.toJson(QJsonDocument::Indented));
}

void MainWindow::exportJson()
{
    // If no json is loaded or is empty
    if (ui->textInput->document()->characterCount() < 2)
        return;
    QUrl url = QFileDialog::getSaveFileUrl(0, "Export JSON File", this->openedUrl.path(), "*.json");
    if (url.isEmpty())
        return;
    exportFile(url);
}

void MainWindow::loadInputFile(QUrl input)
{
    this->statusBar->clearMessage();
    this->openedUrl = input;
    if (input.isLocalFile()) {
        QFile in(input.path());
        if (in.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonParseError err;
            QByteArray arr = in.readAll();
            QJsonDocument doc = QJsonDocument::fromJson(arr, &err);
            ui->textInput->setText(arr);
            if (err.error != QJsonParseError::NoError) {
                this->statusBar->showMessage(err.errorString());
                return qWarning(err.errorString().toLatin1());
            }
            ui->textOutput->setText(arr);

            QStringList enableThese;
            enableThese << "minify" << "prettify" << "export";
            foreach(const QString actionName, enableThese) {
                QAction *act = LoadMenu::actionByName(actionName);
                if (act != NULL)
                    act->setEnabled(true);
            }
        }
        in.close();
    } else {
    }

}

void MainWindow::exportFile(QUrl output)
{
    QFile out(output.path());
    if (out.open(QIODevice::ReadWrite | QIODevice::Text)) {
        out.write(ui->textOutput->toPlainText().toUtf8());
    }
    out.close();
}
