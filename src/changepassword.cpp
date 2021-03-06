#include "headers/changepassword.h"
#include "ui_changepassword.h"
#include <QDesktopWidget>
#include <iostream>

ChangePassword::ChangePassword(QWidget *parent) :
    QWidget(),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    principalref=((Principal*)parent);
    ui->label->setText("Hello "+QString::fromStdString(principalref->getUsername())+
                       ", to change your password, enter with the requested informations below:");
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    QDesktopWidget btt;
    int screenWidth = btt.screen()->width();
    int screenHeight = btt.screen()->height();
    this->setGeometry((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2), width, height);
}

ChangePassword::~ChangePassword()
{
    std::cout<<"Destruindo change Password"<<std::endl;
    delete ui;
}

void ChangePassword::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();

}

void ChangePassword::on_pushButton_clicked()
{
    std::string currentKey= ui->lineEdit->text().toStdString();
    std::string newKey=ui->lineEdit_2->text().toStdString();
    std::cout<<currentKey<<std::endl;
    std::cout<<newKey<<std::endl;
    try{
        principalref->getDao()->changeUserKey(newKey,currentKey);
        QMessageBox qbox;
        qbox.information(0,"Sucesso","Senha alterada com sucesso");
        this->hide();

    }
    catch(InvalidKeyLength &ex){
         principalref->displayErrorMessage(ex.what());
    }
    catch(InvalidKey &ex){
        principalref->displayErrorMessage(ex.what());
    }
    catch(EmptyInputField &ex){
        principalref->displayErrorMessage(ex.what());
    }
    catch(FileIntegrityNotAssured &ex){
        principalref->displayErrorMessage(ex.what());
        principalref->hide();
        principalref->loginref->show();
        this->hide();
    }
}

