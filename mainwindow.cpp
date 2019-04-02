#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    //this->setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(documentModified()));
    this->setWindowTitle("TextEditor[*]");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    MainWindow *newFile = new MainWindow();
    newFile->show();
}

void MainWindow::documentModified()
{
    this->setWindowModified(true);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (this->isWindowModified())
    {
        if (QMessageBox::warning(this,"Document Modified","The document has been modified, do you want to close it? \r\nYou will lose all your changes.","Yes","No",nullptr,1) == 0)
            e->accept();
        else e->ignore();
    }
    else e->accept();
}
