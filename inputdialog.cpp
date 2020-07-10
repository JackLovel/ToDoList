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

void InputDialog::on_buttonReset_clicked()
{
    ui->lineEditDo->clear();
    ui->lineEditId->clear();
    ui->lineEditDate->clear();
    ui->lineEditThing->clear();

    ui->lineEditId->setFocus();
}

void InputDialog::on_pushButton_3_clicked() {}
