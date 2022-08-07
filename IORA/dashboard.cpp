#include "dashboard.h"
#include "ui_dashboard.h"
#include "QVBoxLayout"
#include "QLabel"
#include "tcpclient.h"

Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    connect(&TCPClient::getInstance(), SIGNAL(realTimeInformation(QString)), this, SLOT(newLiveNotification(QString)));

    QFont font = ui->listWidget->font();
    font.setPointSize(16);
    ui->listWidget->setFont(font);

    QString requestMessage = messageEncode::encode(serverRequestTypes::notifications, TCPClient::getUsername());
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    ui->listWidget->clear();
    for(int i = 0 ; i < data.size ; i++)
    {
        addNotification(data.elements[i]);
    }
}

void Dashboard::newLiveNotification(QString message)
{

    QStringList tok = message.split("|");
    if(tok[0].toInt() == serverRequestTypes::newLiveNotification)
    {
        qDebug() << "Real time new notification: " << message;
        ui->listWidget->insertItem(ui->listWidget->currentRow() + 1, tok[1]);
    }
}

void Dashboard::addNotification(QString str)
{
    ui->listWidget->addItem(str);
}

Dashboard::~Dashboard()
{
    delete ui;
}
