#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>
#include <QDebug>
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
    QString title = QString("%1 %2").arg(qApp->applicationName()).arg(qApp->applicationVersion());
	this->aboutAction = new QAction(0);
    this->aboutAction->setMenuRole(QAction::AboutRole);
    this->aboutWindow = new About();
    ui->setupUi(this);
    this->setWindowTitle(title);
    // Unsure if 5.4.0 is when this method name changed, so let's add it into version 5.3.3.
#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
    ui->textInput->setTabStopDistance(ui->textInput->tabStopDistance()/2);
    ui->textOutput->setTabStopDistance(ui->textOutput->tabStopDistance()/2);
#else
    ui->textInput->setTabStopWidth(ui->textInput->tabStopWidth()/2);
    ui->textOutput->setTabStopWidth(ui->textOutput->tabStopWidth()/2);
#endif
    this->defaultLocation = QUrl(QDir::homePath());
    LoadMenu::setupToolBarOn(this, this);
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
    qDebug() << "url" << url;
    if (url.isEmpty())
        return;
    QString inputPath = url.path(); // This will have to be changed when we detect remote files
#ifdef Q_OS_WIN
       if (inputPath.at(0) == "/") { inputPath = inputPath.remove(0, 1); }
#endif
    exportFile(inputPath);
}

void MainWindow::loadInputFile(QUrl input)
{
    // I think there is a bug in 5.3.1 for Windows, where input.path() returns /C:/ (unix root slash prefix)
    // So strip it out for now if at first position and look into fixing it in qt5.
    QString inputPath = input.path();
#ifdef Q_OS_WIN
       if (inputPath.at(0) == "/") { inputPath = inputPath.remove(0, 1); }
#endif
    this->statusBar->clearMessage();
    this->openedUrl = input;
    QFileInfo info = QFileInfo(inputPath);
    if (input.isLocalFile()) {
        QFile in(inputPath);
        qDebug() << "Readable: " <<  in.isReadable() << info.absoluteFilePath() << info.exists();
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
    QFileInfo info(output.path());
    if(info.completeSuffix().isEmpty()) {
        output = QUrl(QString("%1.%2").arg(output.path(), "json"));
    }
    QFile out(output.path());
    if (out.open(QIODevice::ReadWrite | QIODevice::Text)) {
        out.write(ui->textOutput->toPlainText().toUtf8());
    }
    out.close();
}
