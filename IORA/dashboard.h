#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void newLiveNotification(QString message);

private:
    Ui::Dashboard *ui;
    void addNotification(QString str);
};

#endif // DASHBOARD_H
