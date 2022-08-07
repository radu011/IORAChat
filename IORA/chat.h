#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include "QListWidgetItem"

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();

private slots:
    void receiveMessage(QString message);

    void on_listWidget_chatMembers_itemClicked(QListWidgetItem *item);

    void on_lineEdit_Input_returnPressed();

    void on_pushButton_Send_clicked();

private:
    Ui::Chat *ui;

    void updateMemberList();
    void updateChat(QString user2);
};

#endif // CHAT_H
