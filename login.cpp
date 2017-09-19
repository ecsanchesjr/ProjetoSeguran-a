#include "login.h"
#include "ui_login.h"
#include "customexceptions.hpp"
#include <QDesktopWidget>
#include <QPoint>

login::login(QWidget *parent) : QFrame(),
                                ui(new Ui::login)
{
    if (parent == 0)
    {
    }
    else
    {
        principalRef=((Principal*)parent);
        ((Principal*)parent)->closeFromLogin();
    }

    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    //Ajuste da tela
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    QDesktopWidget btt;
    int screenWidth = btt.screen()->width();
    int screenHeight = btt.screen()->height();
    this->setGeometry((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2), width, height);
}

login::~login()
{
    std::cout<<"Encerrando o programa a partir da login"<<std::endl;
    delete ui;
}

void login::closeEvent(QCloseEvent *event){
    std::cout<<"Encerrando o programa a partir da login via close"<<std::endl;
    event->ignore();
    std::cout<<"Antes de encerrar1"<<std::endl;
    std::cout<<principalRef<<std::endl;
    if(principalRef!=nullptr){
        std::cout<<"Entrei na merda"<<std::endl;
        principalRef->closeFromLogin();
    }
    std::cout<<"Antes de encerrar"<<std::endl;
    delete principalRef;
    exit(5);
}

void login::on_pushButton_clicked()
{

    try
    {
        getUsername();
        getPassword();
        dao = new DAO(username, password);
        Principal *p = new Principal(this);
        p->show();
        this->hide();
    }
    catch (UserNotFound &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
    catch (InvalidKey &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
    catch (EmptyInputField &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
    catch (InvalidUserLength &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
    catch (InvalidKeyLength &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
}

std::string login::getUsername()
{
    username = ui->lineEdit_2->text().toStdString();
    return username;
}

std::string login::getPassword()
{
    password = ui->lineEdit->text().toStdString();
    return password;
}

DAO *login::getDao()
{
    return dao;
}

void login::on_pushButton_2_clicked() //Cria user
{
    try
    {
        getUsername();
        getPassword();
        dao->createNewUser(username, password);
        QMessageBox gen;
        gen.information(0, "Sucesso", "Usuário criado com sucesso");
    }
    catch (DuplicatedUser &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
    catch (EmptyInputField &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
    catch (InvalidUserLength &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
    catch (InvalidKeyLength &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
}
