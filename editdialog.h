#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();

    void initInfo();
private slots:
    void on_buttonOk_clicked();

    void on_lineEditCancel_clicked();

    void on_buttonReset_clicked();

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
