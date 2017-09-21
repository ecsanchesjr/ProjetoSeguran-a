#include "headers/login.h"
#include "ui_login.h"
#include "headers/customexceptions.hpp"
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
        principalRef = ((Principal *)parent);
        ((Principal *)parent)->closeFromLogin();
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
    std::cout << "Destruindo  a login" << std::endl;
    if (principalRef != nullptr)
    {
        principalRef->closeFromLogin();
    }
    if (goingToClose)
    {
        delete principalRef;
        delete ui;
        std::cout << "Encerrando completamente" << std::endl;
        exit(5);
    }
}

void login::closeEvent(QCloseEvent *event)
{
    goingToClose = true;
    std::cout << "Encerrando o programa a partir da login via close" << std::endl;
    event->ignore();
    if (principalRef != nullptr)
    {
        principalRef->closeFromLogin();
    }
    delete this;
}

void login::on_pushButton_clicked()
{

    try
    {
        getUsername();
        getPassword();
        dao = new DAO(username, password);
        delete principalRef;
        principalRef = new Principal(this);
        principalRef->show();
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
    catch (FileIntegrityNotAssured &ex)
    {
        // TODO
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

void login::clearFields()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_2->setFocus();
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
    catch (FileIntegrityNotAssured &ex)
    {
        // TODO
        //principalref->displayErrorMessage(ex.what());
    }
}
