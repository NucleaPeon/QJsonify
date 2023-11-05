#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    const QString version = QString("Version %1").arg(qApp->applicationVersion());
 	ui->labelVersionString->setText(version);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
}

About::~About()
{
    delete ui;
}
