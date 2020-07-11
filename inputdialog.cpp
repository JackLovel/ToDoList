#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);

    setWindowTitle("添加信息");
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::initInfo()
{
    ui->lineEditDo->clear();
    ui->lineEditId->clear();
    ui->lineEditDate->clear();
    ui->lineEditThing->clear();

    ui->lineEditId->setFocus();
}
void InputDialog::on_buttonReset_clicked()
{
   initInfo();
}

void InputDialog::on_pushButton_3_clicked() {}

void InputDialog::on_lineEditCancel_clicked()
{
    this->close();
}

void InputDialog::on_buttonOk_clicked()
{

//    Info *info = new Info();
//    info->id = 1;
//    info->operation = "delete,view";
//    info->createDate = "2020/7/1";
//    info->description = "这是一个测试操作";

    Info *info = new Info();
    info->id = ui->lineEditId->text();
    info->operation = ui->lineEditDo->text();
    info->createDate = ui->lineEditDate->text();
    info->description = ui->lineEditThing->text();

    emit sendInfo(info);
    this->close();
}
