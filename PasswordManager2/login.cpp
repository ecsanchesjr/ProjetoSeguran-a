#include "login.h"
#include "ui_login.h"
#include "customexceptions.hpp"

login::login(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{

    try{
        getUsername();
        getPassword();
        dao= new DAO(username,password);
        Principal *p = new Principal(this);
        p->show();
        this->hide();
    }catch(UserNotFound &ex){
        QMessageBox messageBox;
        messageBox.critical(0,"Error",ex.what());
        messageBox.setFixedSize(500,200);
    }
}

std::string login::getUsername(){
    username=ui->lineEdit_2->text().toStdString();
    return username;
}

std::string login::getPassword(){
    password=ui->lineEdit->text().toStdString();
    return password;
}

DAO* login::getDao(){
    return dao;
}
