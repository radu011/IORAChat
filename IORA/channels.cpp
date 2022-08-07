#include "channels.h"
#include "ui_channels.h"
#include "ccreatenewchannel.h"
#include "tcpclient.h"
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>

Channels::Channels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Channels)
{
    ui->setupUi(this);

    connect(&TCPClient::getInstance(), SIGNAL(realTimeInformation(QString)), this, SLOT(receivePost(QString)));
    connect(&TCPClient::getInstance(), SIGNAL(realTimeInformation(QString)), this, SLOT(addNewChannel(QString)));

    ui->stackedWidget_main->setCurrentIndex(0);

    QString requestMessage = messageEncode::encode(serverRequestTypes::belongsChannels, TCPClient::getUsername());
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    for(int i = 0 ; i < data.size ; i++)
    {
        ui->listWidget_Channels->addItem(data.elements[i]);
    }
}

Channels::~Channels()
{
    delete ui;
}

void Channels::addNewChannel(QString message)
{
    QStringList tok = message.split("|");
    if(tok[0].toInt() == serverRequestTypes::newChannelLive)
    {
        qDebug() << "Real time new channel: " << message;
        ui->listWidget_Channels->addItem(tok[1]);
    }
}

void Channels::receivePost(QString message)
{
    QStringList tok = message.split("|");
    if(tok[0].toInt() == serverRequestTypes::newChannelLivePost)
    {
        if(tok[2] == ui->label_channelName->text())
        {
            qDebug() << "Real time post: " << message;
            ui->listWidget_Posts->addItem(tok[1]);
        }
    }
}

void Channels::on_pushButton_newChannel_clicked()
{
    int res;
    QString channelName, channelDescription;

    CcreateNewChannel ps(this);
    res = ps.exec();
    if( res == QDialog::Rejected)
        return;
    channelName = ps.channelName();
    channelDescription = ps.channelDescription();

    QString requestMessage = messageEncode::encode(serverRequestTypes::createChannel, channelName, channelDescription, TCPClient::getUsername());
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    if(data.approval == false)
    {
        QMessageBox::warning(this, "Create channel failed!", "This channel name allready exists.");
    }
    else{
        ui->listWidget_Channels->addItem(channelName);
    }
}


void Channels::on_listWidget_Channels_doubleClicked(const QModelIndex &index)
{
    ui->stackedWidget_main->setCurrentIndex(1);
    ui->stackedWidget_channel->setCurrentIndex(0);

    ui->listWidget_Posts->clear();

    QListWidgetItem *itemFound = ui->listWidget_Channels->takeItem(index.row());
    QString channelName = itemFound->text();
    ui->label_channelName->setText(channelName);

    QString requestMessage = messageEncode::encode(serverRequestTypes::channelPosts, channelName);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData dataPosts = messageDecoder::decode(answerMessage);

    for( int i = 0 ; i < dataPosts.size ; i++)
    {
        ui->listWidget_Posts->addItem(dataPosts.elements[i]);
    }
}


void Channels::on_pushButton_back_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(0);
    ui->listWidget_Posts->clear();

    QString requestMessage = messageEncode::encode(serverRequestTypes::belongsChannels, TCPClient::getUsername());
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    ui->listWidget_Channels->clear();
    for(int i = 0 ; i < data.size ; i++)
    {
        ui->listWidget_Channels->addItem(data.elements[i]);
    }
}

void Channels::on_pushButton_Posts_clicked()
{
    ui->stackedWidget_channel->setCurrentIndex(0);
}


void Channels::on_pushButton_Files_clicked()
{
    ui->stackedWidget_channel->setCurrentIndex(1);
}


void Channels::on_pushButton_Details_clicked()
{
    ui->stackedWidget_channel->setCurrentIndex(2);

    ui->textBrowser_Details->clear();

    QString requestMessage = messageEncode::encode(serverRequestTypes::channelDetails, ui->label_channelName->text());
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData dataDetails = messageDecoder::decode(answerMessage);

    ui->textBrowser_Details->append(QString(" ~Description: " + dataDetails.description));
    ui->textBrowser_Details->append(QString(" ~Owner: " + dataDetails.elements[0]));
    ui->textBrowser_Details->append(QString(" ~Members:"));
    for(int i = 1 ; i < dataDetails.size ; i++)
    {
        ui->textBrowser_Details->append(dataDetails.elements[i]);
    }
}


void Channels::on_pushButton_AddMember_clicked()
{
    QString name = QInputDialog::getText(this, ui->label_channelName->text(), "Add a new member: ");

    QString requestMessage = messageEncode::encode(serverRequestTypes::channelAddNewMember, ui->label_channelName->text(), TCPClient::getUsername(), name);
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    if(data.approval == true)
    {
        ui->textBrowser_Details->append(name);
    }
}

void Channels::on_pushButton_send_clicked()
{
    this->on_lineEdit_textMaker_returnPressed();
}


void Channels::on_lineEdit_textMaker_returnPressed()
{
    QString post = ui->lineEdit_textMaker->text();
    ui->lineEdit_textMaker->clear();

    QString requestMessage = messageEncode::encode(serverRequestTypes::channelNewPost, ui->label_channelName->text(), post, TCPClient::getUsername());
    QString answerMessage = TCPClient::getInstance().getData(requestMessage);
    SmessageData data = messageDecoder::decode(answerMessage);

    qDebug() << data.approval << " " << data.description;

    if(data.approval == true)
    {
        ui->listWidget_Posts->addItem(data.description);
    }
}

void Channels::on_pushButton_CreateMeet_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("Create new meeting");
    dialog.resize(400, 150);
    QList<QLineEdit *> fields;

    QLineEdit *lineEdit1 = new QLineEdit(&dialog);
    QString label1 = QString("Meeting title: ");
    form.addRow(label1, lineEdit1);

    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    QString label2 = QString("Meeting details: ");
    form.addRow(label2, lineEdit2);

    QDateEdit *dateEdit = new QDateEdit(&dialog);
    QString dateLabel = QString("Meeting date: ");
    form.addRow(dateLabel, dateEdit);

    QTimeEdit *timeEdit = new QTimeEdit(&dialog);
    QString timeLabel = QString("Meeting time: ");
    form.addRow(timeLabel, timeEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted)
    {
        // trimite datele aferente intalnirii catre server
        // CERERE: [17|<canal>|<titlu>|<descriere>|<data+ora>]
        // RASPUNS: [17|<postare_intalnire>]
        // TIMP REAL: [102|<postare_intalnire>|<canal>]
    }
}

void Channels::on_pushButton_UploadFile_clicked()
{
    // incarcare fisier
    QString fileName = QFileDialog::getOpenFileName(this, "Upload a file", QDir::homePath());
    QMessageBox::information(this, "..", fileName);

    // trimite fisierul catre server
    // CERERE: [14|<canal>|<owner>|<nume_fisier>|<continut>]
    // RASPUNS: [14|<1/0>|<nume_fisier_afisabil>]
}

void Channels::on_pushButton_DownloadFile_clicked()
{
    // download fisier
    // CERERE: [15|<canal>|<nume_fisier_afisabil>]
    // RASPUNS: [15|<nume_fisier>|<continut>]
}
