#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    selectRow = -1; // 默认的没有选择
    conn = new Connection();

    QStringList header;
    model = new QStandardItemModel();
    header << "序号" << "事情" << "日期" << "操作";
    model->setHorizontalHeaderLabels(header);
    ui->tableView->horizontalHeader()->setStretchLastSection(1);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行，
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
    ui->tableView->setModel(model);

    // http://cn.voidcc.com/question/p-csrholjn-qd.html
    connect(ui->tableView, SIGNAL(cellClicked(int,int)), this, SLOT(displayTodo(int,int)));

    // 新增数据
    inputDialog = new InputDialog();
    connect(inputDialog, SIGNAL(sendInfo(Info*)), this, SLOT(receviedData(Info*)));
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    aboutDialog = new AboutDialog(this);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::openAboutDialog);

    // 修改数据
    editDialog = new EditDialog(this);
    connect(conn, SIGNAL(sendAllData(QVector<Info*>)), this, SLOT(receviedAllData(QVector<Info*>)));


    setWindowTitle("办事清单");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openAboutDialog()
{
    aboutDialog->show();
}
void MainWindow::displayTodo(int row, int/* col*/)
{
//    selectRow = row;
//    qDebug() << "=>" << selectRow;

//    QtableViewItem *itemId = new QtableViewItem;
//    QtableViewItem *itemDescription = new QtableViewItem;
//    QtableViewItem *itemOperation = new QtableViewItem;
//    QtableViewItem *itemDate = new QtableViewItem;

//    itemId = ui->tableView->item(row, 0);
//    itemDescription = ui->tableView->item(row, 1);
//    itemOperation = ui->tableView->item(row, 2);
//    itemDate = ui->tableView->item(row, 3);

//    QString str = QString("序号: %1\n描述：%2\n操作：%3\n时间：%4\n")
//             .arg(itemId->text())
//             .arg(itemDescription->text())
//             .arg(itemOperation->text())
//             .arg(itemDate->text());

//    ui->label->setText(str);
}


void MainWindow::on_pushButton_clicked()
{
    inputDialog->initInfo();
    inputDialog->exec();
}

// 插入数据
void MainWindow::receviedData(Info *info)
{
    conn->insertDb(info);
    conn->loadData();
}

void MainWindow::on_buttonEdit_clicked()
{
    // 如果，用户没有 选择中的任何数据，那么就不触发 更新对话框
    if (selectRow == -1) {
        QMessageBox::warning(this, "警告", "你没有选中数据");
        return;
    }

    editDialog->initInfo();
    editDialog->exec();
}

// 发出调用数据请求
void MainWindow::on_buttonLoadData_clicked()
{
    conn->loadData();
}

// 接收所有数据
void MainWindow::receviedAllData(QVector<Info *> infos)
{
    this->displayTable(infos);
}

// 显示数据表
void MainWindow::displayTable(QVector<Info *> infoVector)
{
    if (infoVector.isEmpty()) {
        return;
    }

    int row = 0;
    for (int i = 0; i < infoVector.size(); i++) {
        row = i;
        Info *info = infoVector.at(i);

        model->setItem(row, 0, new QStandardItem(info->id));
        model->setItem(row, 1, new QStandardItem(info->description));
        model->setItem(row, 2, new QStandardItem(info->createDate));
        model->setItem(row, 3, new QStandardItem(info->operation));
     }
}
