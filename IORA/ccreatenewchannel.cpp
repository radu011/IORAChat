#include "ccreatenewchannel.h"
#include "ui_ccreatenewchannel.h"

CcreateNewChannel::CcreateNewChannel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CcreateNewChannel)
{
    ui->setupUi(this);
    setWindowTitle("Create new channel");
}

CcreateNewChannel::~CcreateNewChannel()
{
    delete ui;
}

void CcreateNewChannel::on_buttonBox_accepted()
{
    accept();
}

void CcreateNewChannel::on_buttonBox_rejected()
{
    reject();
}

QString CcreateNewChannel::channelName() const
{
    return ui->lineEdit_name->text();
}

QString CcreateNewChannel::channelDescription() const
{
    return ui->lineEdit->text();
}
