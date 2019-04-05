#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QFontDialog>
#include <QMessageBox>
#include <QSettings>
#include <QTextStream>

MainWindow::MainWindow(const QString &fileName, QWidget *parent) :
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

    loadFile(fileName);

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveFileAs()));
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
        switch (QMessageBox::warning(this, "Document Modified", "The document has been modified. Do you want to save your changes?\nYou will lose any unsaved changes.", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Cancel)) {
        case QMessageBox::Yes:
            if (saveFile()) e->accept();
            else e->ignore();
            break;
        case QMessageBox::No:
            e->accept();
            break;
        case QMessageBox::Cancel:
            e->ignore();
            break;
        default: e->ignore();
        }
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

void MainWindow::loadFile(const QString &fileName)
{
    if (fileName.isEmpty())
    {
        setFileName(QString());
        return;
    }

    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Error","Couldn't open file");
        setFileName(QString());
        return;
    }

    QTextStream input(file);
    ui->textEdit->setText( input.readAll() );

    file->close();
    delete file;

    setFileName(fileName);
    this->setWindowModified(false);
}

void MainWindow::setFileName(const QString &fileName)
{
    m_fileName = fileName;
    this->setWindowTitle(QString("%1[*] - %2")
                         .arg(m_fileName.isNull()?"untitled":QFileInfo(m_fileName).fileName())
                         .arg(QApplication::applicationName()));
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open document", QDir::currentPath(), "Text documents (*.txt)");
    if (fileName.isNull()) return;

    if (this->m_fileName.isNull() && !this->isWindowModified()) loadFile((fileName));
    else
    {
        MainWindow *newFile = new MainWindow(fileName);
        newFile->show();
    }

}

bool MainWindow::saveFile()
{
    if (m_fileName.isNull()) return saveFileAs();
    else {
       QFile *file = new QFile(m_fileName);
       if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QMessageBox::warning(this, "Error", "File couldn't be saved");
           setFileName(QString());
           return false;
       }
       else {
           QTextStream stream(file);
           stream << ui->textEdit->toPlainText();
       }
       file->close();
       this->setWindowModified(false);
       return true;
    }
}

bool MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document", m_fileName.isNull()?QDir::currentPath():m_fileName, "Text documents (*.txt)");
    if (fileName.isNull()) return false;
    else
    {
        setFileName(fileName);
        return saveFile();
    }
}
