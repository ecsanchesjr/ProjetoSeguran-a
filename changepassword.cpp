#include "changepassword.h"
#include "ui_changepassword.h"
#include <iostream>
ChangePassword::ChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
}

ChangePassword::~ChangePassword()
{
    std::cout<<"Deletando change Password"<<std::endl;
    delete ui;
}
