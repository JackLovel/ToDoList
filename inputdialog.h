#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include "info.h"

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

signals:
    void sendInfo(Info *info);

private slots:
    void on_pushButton_3_clicked();

    void on_buttonReset_clicked();

    void on_lineEditCancel_clicked();

    void on_buttonOk_clicked();

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
