#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);

    setWindowTitle("修改信息");
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::initInfo()
{
    ui->lineEditDo->clear();
    ui->lineEditId->clear();
    ui->lineEditDate->clear();
    ui->lineEditThing->clear();

    ui->lineEditId->setFocus();
}

void EditDialog::on_buttonOk_clicked()
{
    // 存放修改 数据的逻辑 代码
}

void EditDialog::on_lineEditCancel_clicked()
{
    this->close();
}

void EditDialog::on_buttonReset_clicked()
{
    // 清空所有已经填写 数据
    this->initInfo();
}
