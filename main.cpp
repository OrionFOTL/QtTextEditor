#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.setApplicationName("Text Editor");
    a.setApplicationVersion("0.1");
    a.setOrganizationName("OrionSoft");
    a.setOrganizationDomain("example.com");

    a.setWindowIcon(QIcon(":/icons/new.png"));

    return a.exec();
}
