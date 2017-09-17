#ifndef LOGIN_H
#define LOGIN_H

#include <QFrame>
#include <string>
#include "principal.h"
#include "DAO.hpp"
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
private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
    std::string username;
    std::string password;
    DAO* dao = nullptr;
};

#endif // LOGIN_H
