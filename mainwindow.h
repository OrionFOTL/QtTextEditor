#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_actionNew_triggered();
    void documentModified();

    void on_actionSelectFont_triggered();

private:
    Ui::MainWindow *ui;
    QSettings settings;
};

#endif // MAINWINDOW_H
