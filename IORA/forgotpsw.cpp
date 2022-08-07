#include "forgotpsw.h"
#include "ui_forgotpsw.h"
#include "QMessageBox"
#include "tcpclient.h"

ForgotPsw::ForgotPsw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotPsw)
{
    ui->setupUi(this);
}

ForgotPsw::~ForgotPsw()
{
    delete ui;
}

void ForgotPsw::on_pushButton_submit_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString email = ui->lineEdit_email->text();

    QString requestMessage = messageEncode::encode(serverRequestTypes::resetPassword, username, email);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    if(data.approval == true)
    {
        QMessageBox::information(this, "Succes", "The e-mail was send, check it!");
        this->close();
        this->parentWidget()->show();
    }
    else
    {
        QMessageBox::warning(this, "Failed", "The credentials doesn't match!");
    }
}


void ForgotPsw::on_pushButton_clicked()
{
    this->close();
    this->parentWidget()->show();
}


void ForgotPsw::on_lineEdit_email_returnPressed()
{
    this->on_pushButton_submit_clicked();
}

