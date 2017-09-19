#ifndef LOGIN_H
#define LOGIN_H

#include <QFrame>
#include <string>
#include <QMessageBox>
#include "principal.h"
#include "DAO.hpp"
class Principal;
namespace Ui {
class login;
}

class login : public QFrame
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    std::string getUsername();
    std::string getPassword();
    DAO* getDao(); //Utilizar para pegar a DAO
    Principal* principalRef=nullptr;
    bool goingToClose=false;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void closeEvent(QCloseEvent *);

private:
    Ui::login *ui;
    std::string username;
    std::string password;
    DAO* dao = nullptr;
};

#endif // LOGIN_H
