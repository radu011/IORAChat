#ifndef FORGOTPSW_H
#define FORGOTPSW_H

#include <QDialog>

namespace Ui {
class ForgotPsw;
}

class ForgotPsw : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPsw(QWidget *parent = nullptr);
    ~ForgotPsw();

private slots:
    void on_pushButton_submit_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_email_returnPressed();

private:
    Ui::ForgotPsw *ui;
};

#endif // FORGOTPSW_H
