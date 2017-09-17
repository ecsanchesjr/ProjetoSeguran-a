#include "login.h"
#include "ui_login.h"

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
    Principal *p = new Principal(this);
    p->show();
    this->hide();
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
    dao= new DAO(username,password);
    return dao;
}
