#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#ifdef Q_OS_MAC
#include "lib/cocoainitializer/cocoainitializer.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef Q_OS_MAC
    CocoaInitializer initializer;
    Q_UNUSED(initializer)
#else
    a.setWindowIcon(QIcon(":/icons/qjsonify-64x64.png"));
#endif
    a.setApplicationName(QObject::tr("QJsonify"));
    a.setApplicationVersion("1.0.1");
    MainWindow w;
    w.show();

    return a.exec();
}
