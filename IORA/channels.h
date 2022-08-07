#ifndef CHANNELS_H
#define CHANNELS_H

#include <QWidget>

namespace Ui {
class Channels;
}

class Channels : public QWidget
{
    Q_OBJECT

public:
    explicit Channels(QWidget *parent = nullptr);
    ~Channels();

private slots:
    void addNewChannel(QString message);

    void receivePost(QString message);

    void on_pushButton_newChannel_clicked();

    void on_listWidget_Channels_doubleClicked(const QModelIndex &index);

    void on_pushButton_back_clicked();

    void on_pushButton_Posts_clicked();

    void on_pushButton_Files_clicked();

    void on_pushButton_Details_clicked();

    void on_pushButton_AddMember_clicked();

    void on_pushButton_send_clicked();

    void on_lineEdit_textMaker_returnPressed();

    void on_pushButton_UploadFile_clicked();

    void on_pushButton_CreateMeet_clicked();

    void on_pushButton_DownloadFile_clicked();

private:
    Ui::Channels *ui;
};

#endif // CHANNELS_H
