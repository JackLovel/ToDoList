#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int row = 100;
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
