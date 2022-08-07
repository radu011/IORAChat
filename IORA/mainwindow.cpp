#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "QVBoxLayout"

#include "tcpclient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();


    QString requestMessage = messageEncode::encode(serverRequestTypes::verifyCredentials, username, password);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    if(data.approval == true)
    {
        TCPClient::setUsername(username);
        QMessageBox::information(this, "Login", "Username and password is correct");
        this->hide();
        this->mainPage = new mainApp;
        this->mainPage->show();
    }
    else
    {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
        ui->lineEdit_password->clear();
    }
}


void MainWindow::on_pushButton_register_clicked()
{
    this->hide();
    this->registerP = new registerPage(this);
    this->registerP->show();
}


void MainWindow::on_pushButton_forgotPass_clicked()
{
    this->hide();
    this->forgotPswPage = new ForgotPsw(this);
    this->forgotPswPage->show();
}


void MainWindow::on_lineEdit_password_returnPressed()
{
    this->on_pushButton_Login_clicked();
}

