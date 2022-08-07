#ifndef CCREATENEWCHANNEL_H
#define CCREATENEWCHANNEL_H

#include <QDialog>

namespace Ui {
class CcreateNewChannel;
}

class CcreateNewChannel : public QDialog
{
    Q_OBJECT

public:
    explicit CcreateNewChannel(QWidget *parent = nullptr);
    ~CcreateNewChannel();

    QString channelName() const;
    QString channelDescription() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CcreateNewChannel *ui;
};

#endif // CCREATENEWCHANNEL_H
