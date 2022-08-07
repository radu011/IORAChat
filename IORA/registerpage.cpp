#include "registerpage.h"
#include "ui_registerpage.h"
#include "QMessageBox"
#include "tcpclient.h"

registerPage::registerPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerPage)
{
    ui->setupUi(this);

}

registerPage::~registerPage()
{
    delete ui;
}

void registerPage::on_pushButton_submit_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password1 = ui->lineEdit_password1->text();
    QString password2 = ui->lineEdit_password2->text();
    QString email = ui->lineEdit_email->text();

    QString requestMessage = messageEncode::encode(serverRequestTypes::signIn, username, password1, email);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    if(password1 != password2)
    {
        QMessageBox::warning(this,"Register failed", "Password doesn't match!");
        ui->lineEdit_password2->clear();
        ui->lineEdit_password1->clear();
    }
    if(data.approval == false)
    {
        QMessageBox::warning(this,"Register failed", "Username allready exists!");
        ui->lineEdit_username->clear();
        ui->lineEdit_password1->clear();
        ui->lineEdit_password2->clear();
        ui->lineEdit_email->clear();
    }

    this->close();
    this->parentWidget()->show();
}
