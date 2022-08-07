#include "chat.h"
#include "ui_chat.h"
#include "tcpclient.h"

Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    updateMemberList();
    connect(&TCPClient::getInstance(), SIGNAL(realTimeInformation(QString)), this, SLOT(receiveMessage(QString)));
}

void Chat::receiveMessage(QString message)
{
    QStringList tok = message.split("|");
    if(tok[0].toInt() == serverRequestTypes::newChatLiveMessage)
    {
        if(tok[2] == TCPClient::getUsername())
        {
            if(tok[1] == ui->listWidget_chatMembers->currentItem()->text())
            {
                ui->textBrowser_conversatie->append(tok[3]);
            }
        }
    }
}

void Chat::updateMemberList()
{
    QString requestMessage = messageEncode::encode(serverRequestTypes::chatMembers);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    QString usernameLocal = TCPClient::getUsername();
    for(int i = 0 ; i < data.size ; i++)
    {
        if(usernameLocal != data.elements[i])
            ui->listWidget_chatMembers->addItem(data.elements[i]);
    }
}

void Chat::updateChat(QString user2)
{
    QString requestMessage = messageEncode::encode(serverRequestTypes::chatConversation, TCPClient::getUsername(), user2);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    ui->textBrowser_conversatie->clear();

    for(int i = 0 ; i < data.size ; i++)
    {
        ui->textBrowser_conversatie->append(data.elements[i]);
    }
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_listWidget_chatMembers_itemClicked(QListWidgetItem *item)
{
    QString destinationUsername = item->text();
    updateChat(destinationUsername);
}

void Chat::on_lineEdit_Input_returnPressed()
{
    on_pushButton_Send_clicked();
}

void Chat::on_pushButton_Send_clicked()
{
    QString destinationUsername = ui->listWidget_chatMembers->currentItem()->text();
    QString message = ui->lineEdit_Input->text();
    ui->lineEdit_Input->clear();

    QString requestMessage = messageEncode::encode(serverRequestTypes::chatSendMessage, TCPClient::getUsername(), destinationUsername, message);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    QStringList tok = answerMessage.split("|");
    data.destination = tok[2];

    if(data.approval == true)
    {
        ui->textBrowser_conversatie->append(data.destination);
    }
}
