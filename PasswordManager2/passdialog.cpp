#include "passdialog.h"
#include "ui_passdialog.h"
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
    else if(op==4){
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(deleteUser()));
    }
}

passDialog::passDialog(QWidget *parent,QWidget *addEntryWin, string site, string login, string pass) : QWidget(),
                                                                                  ui(new Ui::passDialog)
{
    ui->setupUi(this);
    principalref = (Principal *)parent;
    addEntryPtr = (addEntry *)addEntryWin;
    this->site = site;
    this->nick = login;
    this->pass = pass;
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(newEntry()));
}

void passDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    delete ui;
}

passDialog::~passDialog()
{
    delete ui;
}

void passDialog::newEntry()
{
    try{
        std::string straux = principalref->indexPane;
    
        std::string key = ui->lineEdit->text().toStdString();
        
        principalref->getDao()->createNewEntry(site, nick, pass, key);
        principalref->redrawAll();
        
        addEntryPtr->hide();
        delete addEntryPtr;

        this->hide();
        delete this;
    }catch(InvalidKey &ex){
        principalref->displayInvalidPass(ex.what());
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

        principalref->getDao()->modifyEntry(name, login, pass, key,newname);

        principalref->redrawAll();
        this->hide();
        delete ui;
    }
    catch (InvalidKey &ex)
    {
        principalref->displayInvalidPass(ex.what());
    }
}

void passDialog::go()
{
    try
    {
        std::string straux = principalref->indexPane;
        std::string key = ui->lineEdit->text().toStdString(), name = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->objectName().toStdString();
        std::vector<std::string> entry = principalref->getDao()->getEntry(name, key);
        //atualiza o campo do password da entrada
        principalref->senhasRefs[std::stoi(straux.substr(4, 4))]->setText(QString::fromStdString(entry[2]));
        std::cout<<(principalref->sitesRefs)[std::stoi(straux.substr(4, 4))]->objectName().toStdString()<<std::endl;
        this->hide();
        delete ui;
    }
    catch (InvalidKey &ex)
    {
        principalref->displayInvalidPass(ex.what());
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
        principalref->redrawAll(); //Redesenha a tela
        this->hide();
        delete ui;//NÃO ESQUECER DE DELETAR SE USAR PONTEIRO, ELE NUNCA SAI DE ESCOPO
    }
    catch (InvalidKey &ex)
    {
        principalref->displayInvalidPass(ex.what());
    }
}

void passDialog::deleteUser(){
    std::cout<<"Delete user"<<std::endl;
    std::string passTemp =  ui->lineEdit->text().toStdString();
    try{
        principalref->getDao()->deleteUser(passTemp);
        std::cout<<"User deletado com sucesso!"<<std::endl;
        QMessageBox* qbox= new QMessageBox;
        qbox->information(this,"Usuário Deletado","Usuário deletado com sucesso");
        delete qbox;
        login *lg = new login(principalref);
        lg->show();
        this->hide();
        delete ui;
    }
    catch(InvalidKey &ex){
        principalref->displayInvalidPass(ex.what());
    }
}
