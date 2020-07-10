#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

private slots:
    void on_pushButton_3_clicked();

    void on_buttonReset_clicked();

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
