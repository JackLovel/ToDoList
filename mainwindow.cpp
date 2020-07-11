#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int row = 0;
    int col = 4;
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setRowCount(row);

    QStringList header;
    header << "序号" << "事情" << "日期" << "操作";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行，
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
    ui->tableWidget->show();

    connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),
            this,SLOT(DoubleClickFun(QTableWidgetItem*)));

    inputDialog = new InputDialog();
    connect(inputDialog, SIGNAL(sendInfo(Info*)), this, SLOT(receviedData(Info*)));

    setWindowTitle("办事清单");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DoubleClickFun(QTableWidgetItem */*item*/)
{
    qDebug() << "我被单击了";
}


void MainWindow::on_pushButton_clicked()
{
    inputDialog->exec();
}

void MainWindow::receviedData(Info *info)
{
//    info->toString();
    QString id = info->id;
    QString description = info->description;
    QString date = info->createDate;
    QString operation = info->operation;


    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount); // 增加一行
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(id));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(description));
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(date));
    ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(operation));
}
