#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>

#include "aboutdialog.h"
#include "inputdialog.h"
#include "info.h"
#include "connection.h"
#include "inputdialog.h"
#include "editdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayTable(QVector<Info *> infoVector);
    void flushData(); // 刷新数据
private slots:
    void displayInfo(const QModelIndex &index);

    void on_pushButton_clicked();

    void receviedData(Info *info);
    void receviedAllData(QVector<Info*> infos);

    void openAboutDialog();

    void on_buttonEdit_clicked();

    void on_buttonLoadData_clicked();

signals:
    void sendInfoEdit(Info *info);

private:
    Ui::MainWindow *ui;

    InputDialog *inputDialog;
    AboutDialog *aboutDialog;
    EditDialog *editDialog;

    QStandardItemModel *model;

    Connection *conn;

    int selectRow;
    int tableCol;
};
#endif // MAINWINDOW_H
