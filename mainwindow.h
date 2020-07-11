#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "inputdialog.h"
#include "info.h"

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
    void DoubleClickFun(QTableWidgetItem* item);
//    void cellDoubleClicked(int row, int column);

    void testSlot(int row, int col);

    void on_pushButton_clicked();

    void receviedData(Info *info);

private:
    Ui::MainWindow *ui;

    InputDialog *inputDialog;
};
#endif // MAINWINDOW_H
