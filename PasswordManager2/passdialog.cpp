#include "passdialog.h"
#include "ui_passdialog.h"
passDialog::passDialog(QWidget *parent, int op) : QWidget(),
                                                  ui(new Ui::passDialog)
{
    ui->setupUi(this);
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
}

passDialog::passDialog(QWidget *parent,QWidget *addEntryWin, string site, string login, string pass) : QWidget(),
                                                                                  ui(new Ui::passDialog)
{
    ui->setupUi(this);
    principalref = (Principal *)parent;
    addEntryPtr = (addEntry *)addEntryWin;
    this->site = site;
    this->login = login;
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
        
        principalref->getDao()->createNewEntry(site, login, pass, key);
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
                    name = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->text().toStdString(),
                    login = principalref->nicksRefs[std::stoi(straux.substr(4, 4))]->text().toStdString(),
                    pass = principalref->senhasRefs[std::stoi(straux.substr(4, 4))]->text().toStdString();

        principalref->getDao()->modifyEntry(name, login, pass, key);

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
        std::string key = ui->lineEdit->text().toStdString(), name = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->text().toStdString();
        std::vector<std::string> entry = principalref->getDao()->getEntry(name, key);

        //atualiza o campo do password da entrada
        principalref->senhasRefs[std::stoi(straux.substr(4, 4))]->setText(QString::fromStdString(entry[2]));

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
        std::string entrada = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->text().toStdString();
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
