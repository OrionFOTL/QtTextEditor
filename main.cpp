#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Text Editor");
    a.setApplicationVersion("0.1");
    a.setOrganizationName("OrionSoft");
    a.setOrganizationDomain("example.com");
    a.setWindowIcon(QIcon(":/icons/new.png"));

    MainWindow w;
    w.show();

    return a.exec();
}
