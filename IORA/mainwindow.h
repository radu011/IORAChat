#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainapp.h"
#include "registerpage.h"
#include "forgotpsw.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private slots:
    void on_pushButton_Login_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_forgotPass_clicked();

    void on_lineEdit_password_returnPressed();

private:
    Ui::MainWindow *ui;
    mainApp* mainPage;
    registerPage* registerP;
    ForgotPsw* forgotPswPage;
};
#endif // MAINWINDOW_H
