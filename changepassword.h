#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QWidget>
#include <QCloseEvent>
#include "principal.h"
class Principal;
namespace Ui {
class ChangePassword;
}

class ChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = 0);
    ~ChangePassword();
    Principal *principalref=nullptr;

private:
    Ui::ChangePassword *ui;

private slots:
    void closeEvent(QCloseEvent *);
    void on_pushButton_clicked();
};

#endif // CHANGEPASSWORD_H
