#include "mainapp.h"
#include "ui_mainapp.h"

#include "dashboard.h"
#include "channels.h"
#include "chat.h"
#include "calendar.h"

mainApp::mainApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainApp)
{
    ui->setupUi(this);
    ui->tabWidget_main->clear();

    dashboard = new Dashboard(this);
    channels = new Channels(this);
    chat = new Chat(this);
    calendar = new Calendar(this);

    ui->tabWidget_main->addTab(dashboard, QString("Dashboard"));
    ui->tabWidget_main->addTab(channels, QString("Channels"));
    ui->tabWidget_main->addTab(chat, QString("Chat"));
    ui->tabWidget_main->addTab(calendar, QString("Calendar"));
}

mainApp::~mainApp()
{
    delete ui;
}
