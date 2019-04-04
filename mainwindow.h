#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &fileName=QString(), QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_actionNew_triggered();
    void documentModified();

    void on_actionSelectFont_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    QString m_fileName;
    void loadFile(const QString &fileName);
    void setFileName(const QString &m_fileName);
};

#endif // MAINWINDOW_H
