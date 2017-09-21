#include "headers/passdialog.h"
#include "ui_passdialog.h"
#include <QDesktopWidget>

passDialog::passDialog(QWidget *parent, int op) : QWidget(),
                                                  ui(new Ui::passDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    principalref = (Principal *)parent;
    if (op == 1)
    {
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(go()));
    }
    else if (op == 2)
    {
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(remove()));
    }
    else if (op == 3)
    {
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(modify()));
    }
    else if (op == 4)
    {
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(deleteUser()));
    }
    //Ajuste da tela
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    QDesktopWidget btt;
    int screenWidth = btt.screen()->width();
    int screenHeight = btt.screen()->height();
    this->setGeometry((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2), width, height);
}

passDialog::passDialog(QWidget *parent, QWidget *addEntryWin, string site, string login, string pass) : QWidget(),
                                                                                                        ui(new Ui::passDialog)
{
    principalref = (Principal *)parent;
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    addEntryPtr = (addEntry *)addEntryWin;
    this->site = site;
    this->nick = login;
    this->pass = pass;
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(newEntry()));
    //Ajuste da tela
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    QDesktopWidget btt;
    int screenWidth = btt.screen()->width();
    int screenHeight = btt.screen()->height();
    this->setGeometry((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2), width, height);
}

void passDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

passDialog::~passDialog()
{
    std::cout << "Destruindo PassDialog" << std::endl;
    principalref->pD = nullptr;
    delete ui;
}

void passDialog::newEntry()
{
    try
    {
        std::string straux = principalref->indexPane;

        std::string key = ui->lineEdit->text().toStdString();

        principalref->getDao()->createNewEntry(site, nick, pass, key);
        principalref->setPassword(key);
        principalref->redrawAll();
        principalref->setPassword("");

        addEntryPtr->hide();
        delete principalref->ae;
        principalref->ae = nullptr;
        this->hide();
    }
    catch (InvalidKey &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (EmptyInputField &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (DuplicatedEntry &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (FileIntegrityNotAssured &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
}

void passDialog::modify()
{
    try
    {
        std::string straux = principalref->indexPane;
        std::string key = ui->lineEdit->text().toStdString(),
                    name = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->objectName().toStdString(),
                    login = principalref->nicksRefs[std::stoi(straux.substr(4, 4))]->text().toStdString(),
                    pass = principalref->senhasRefs[std::stoi(straux.substr(4, 4))]->text().toStdString(),
                    newname = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->text().toStdString();
        principalref->getDao()->modifyEntry(name, login, pass, key, newname);
        principalref->setPassword(key);
        principalref->redrawAll();
        principalref->setPassword("");
        this->hide();
    }
    catch (InvalidKey &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (EmptyInputField &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (DuplicatedEntry &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (FileIntegrityNotAssured &ex)
    {
        principalref->displayErrorMessage(ex.what());
        principalref->hide();
        principalref->loginref->show();
    }
}

void passDialog::go()
{
    try
    {
        std::string straux = principalref->indexPane;
        std::string key = ui->lineEdit->text().toStdString(), name = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->objectName().toStdString();
        std::vector<std::string> entry = principalref->getDao()->getEntry(name, key);
        //atualiza o site da entrada
        principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->setText(QString::fromStdString(entry[0]));
        //atualiza o nick da entrada
        principalref->nicksRefs[std::stoi(straux.substr(4, 4))]->setText(QString::fromStdString(entry[1]));
        //atualiza o campo do password da entrada
        principalref->senhasRefs[std::stoi(straux.substr(4, 4))]->setText(QString::fromStdString(entry[2]));
        this->hide();
    }
    catch (InvalidKey &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (EmptyInputField &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (FileIntegrityNotAssured &ex)
    {
        principalref->displayErrorMessage(ex.what());
        principalref->hide();
        principalref->loginref->show();
    }
}

void passDialog::remove()
{
    try
    {
        std::string straux = principalref->indexPane;
        std::string entrada = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->objectName().toStdString();
        std::string temppass = ui->lineEdit->text().toStdString();
        principalref->getDao()->deleteEntry(entrada, temppass);
        //Remove o pane
        delete (principalref->sitesRefs)[std::stoi(straux.substr(4, 4))];                                    //Deleta o elemento
        (principalref->sitesRefs).erase((principalref->sitesRefs).begin() + std::stoi(straux.substr(4, 4))); //Deleta a referencia do elemento no index
        delete (principalref->nicksRefs)[std::stoi(straux.substr(4, 4))];
        (principalref->nicksRefs).erase((principalref->nicksRefs).begin() + std::stoi(straux.substr(4, 4)));
        delete (principalref->senhasRefs)[std::stoi(straux.substr(4, 4))];
        (principalref->senhasRefs).erase((principalref->senhasRefs).begin() + std::stoi(straux.substr(4, 4)));
        delete (principalref->bFramesRefs)[std::stoi(straux.substr(4, 4))];
        (principalref->bFramesRefs).erase((principalref->bFramesRefs).begin() + std::stoi(straux.substr(4, 4)));
        delete (principalref->paneRefs)[std::stoi(straux.substr(4, 4))];
        (principalref->paneRefs).erase((principalref->paneRefs).begin() + std::stoi(straux.substr(4, 4)));
        delete (principalref->cFramesRefs)[std::stoi(straux.substr(4, 4))];
        (principalref->cFramesRefs).erase((principalref->cFramesRefs).begin() + std::stoi(straux.substr(4, 4)));
        principalref->setPassword(temppass);
        principalref->redrawAll(); //Redesenha a tela
        principalref->setPassword("");
        this->hide();
    }
    catch (InvalidKey &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (EmptyInputField &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (FileIntegrityNotAssured &ex)
    {
        principalref->displayErrorMessage(ex.what());
        principalref->hide();
        principalref->loginref->show();
    }
}

void passDialog::deleteUser()
{
    std::cout << "Delete user" << std::endl;
    std::string passTemp = ui->lineEdit->text().toStdString();
    try
    {
        principalref->getDao()->deleteUser(passTemp);
        std::cout << "User deletado com sucesso!" << std::endl;
        QMessageBox *qbox = new QMessageBox;
        qbox->information(this, "Usuário Deletado", "Usuário deletado com sucesso");
        delete qbox;
        principalref->loginref->show();
        principalref->hide();
        this->hide();
    }
    catch (InvalidKey &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (EmptyInputField &ex)
    {
        principalref->displayErrorMessage(ex.what());
    }
    catch (FileIntegrityNotAssured &ex)
    {
        principalref->displayErrorMessage(ex.what());
        principalref->hide();
        principalref->loginref->show();
    }
}
