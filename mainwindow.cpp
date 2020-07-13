#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    selectRow = -1; // 默认的没有选择
    tableCol = 4;
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
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(displayInfo(const QModelIndex &)));
//    connect(ui->tableView, SIGNAL(doubleClicked(int,int)), this, SLOT(displayTodo(int,int)));

    // 新增数据
    inputDialog = new InputDialog();
    connect(inputDialog, SIGNAL(sendInfo(Info*)), this, SLOT(receviedData(Info*)));
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    aboutDialog = new AboutDialog(this);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::openAboutDialog);

    // 修改数据
    editDialog = new EditDialog(this);
    connect(conn, SIGNAL(sendAllData(QVector<Info*>)), this, SLOT(receviedAllData(QVector<Info*>)));


    // 加载数据
    flushData();

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
void MainWindow::displayInfo(const QModelIndex & index)
{
    selectRow = index.row();

    QString id = model->index(selectRow, 0).data().toString();
    QString description = model->index(selectRow, 1).data().toString();
    QString createDate = model->index(selectRow, 2).data().toString();
    QString operation = model->index(selectRow, 3).data().toString();

    QString str = QString("序号: %1\n事情：%2\n操作：%3\n日期：%4\n")
             .arg(id)
             .arg(description)
             .arg(operation)
             .arg(createDate);

    ui->label->setText(str);

//    Info *info = new Info();
//    info->id = id;
//    info->description = description;
//    info->createDate = createDate;
//    info->operation = operation;
}


void MainWindow::on_pushButton_clicked()
{
    inputDialog->initInfo();
    inputDialog->exec();
}

void MainWindow::flushData()
{
    conn->loadData();
}
// 插入数据
void MainWindow::receviedData(Info *info)
{
    conn->insertDb(info);
    flushData();
}

void MainWindow::on_buttonEdit_clicked()
{
    // 如果，用户没有 选择中的任何数据，那么就不触发 更新对话框
    if (selectRow == -1) {
        QMessageBox::warning(this, "警告", "你没有选中数据");
        return;
    }

    QString id = model->index(selectRow, 0).data().toString();
    QString description = model->index(selectRow, 1).data().toString();
    QString createDate = model->index(selectRow, 2).data().toString();
    QString operation = model->index(selectRow, 3).data().toString();

    Info *info = new Info();
    info->id = id;
    info->description = description;
    info->createDate = createDate;
    info->operation = operation;

    emit sendInfoEdit(info);

//    editDialog->initInfo();
    editDialog->exec();
}

// 发出调用数据请求
void MainWindow::on_buttonLoadData_clicked()
{
    flushData();
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
