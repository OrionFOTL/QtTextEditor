#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFontDialog>
#include <QMessageBox>
#include <QSettings>

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

    QSettings settings;
    QVariant fontValue = settings.value("viewFont");
    QFont chosenFont = fontValue.value<QFont>();
    ui->textEdit->setFont(chosenFont);

    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionCut, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    connect(ui->actionCopy, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    connect(ui->actionPaste, SIGNAL(triggered()), ui->textEdit, SLOT(paste()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->textEdit, SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), ui->textEdit, SLOT(redo()));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));
    
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
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

void MainWindow::on_actionSelectFont_triggered()
{
    bool ok;
    QFont chosenFont = QFontDialog::getFont(&ok,ui->textEdit->font(),this);
    if (ok) ui->textEdit->setFont(chosenFont);

    QSettings settings;
    settings.setValue("viewFont",chosenFont);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About this application", "Simple text editor with multiple windows and customizable font");
}
