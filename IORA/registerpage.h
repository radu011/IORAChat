#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QDialog>

namespace Ui {
class registerPage;
}

class registerPage : public QDialog
{
    Q_OBJECT

public:
    explicit registerPage(QWidget *parent = nullptr);
    ~registerPage();

private slots:
    void on_pushButton_submit_clicked();

private:
    Ui::registerPage *ui;
};

#endif // REGISTERPAGE_H
