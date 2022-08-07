#ifndef MAINAPP_H
#define MAINAPP_H

#include <QDialog>

namespace Ui {
class mainApp;
}

class Dashboard;
class Channels;
class Chat;
class Calendar;

class mainApp : public QDialog
{
    Q_OBJECT

public:
    explicit mainApp(QWidget *parent = nullptr);
    ~mainApp();

private:
    Ui::mainApp *ui;

    Dashboard* dashboard;
    Channels* channels;
    Chat* chat;
    Calendar* calendar;
};

#endif // MAINAPP_H
