#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "aboutdialog.h"
#include "inputdialog.h"
#include "info.h"
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void displayTodo(int row, int col);

    void on_pushButton_clicked();

    void receviedData(Info *info);
    void openAboutDialog();

private:
    Ui::MainWindow *ui;

    InputDialog *inputDialog;
    AboutDialog *aboutDialog;
};
#endif // MAINWINDOW_H
