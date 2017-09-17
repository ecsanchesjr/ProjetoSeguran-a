#include "passdialog.h"
#include "ui_passdialog.h"
passDialog::passDialog(QWidget *parent) :
    QWidget(),
    ui(new Ui::passDialog)
{
    ui->setupUi(this);
    principalref= (Principal*)parent;
    if(principalref->typeop==1){
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(go()));
    }
    else if(principalref->typeop==2){
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(remove()));
    }

}

void passDialog::closeEvent(QCloseEvent *event){
    event->ignore();
    this->hide();
}

passDialog::~passDialog()
{
    delete ui;
}

void passDialog::go(){
    std::cout<<"GoPassDialog"<<std::endl;
}

void passDialog::remove(){
    try
    {
        std::string straux= principalref->indexPane;
        std::string entrada = principalref->sitesRefs[std::stoi(straux.substr(4, 4))]->text().toStdString();
        std::string temppass=ui->lineEdit->text().toStdString();
        principalref->getDao()->deleteEntry(entrada,temppass);
        //Remove o pane
        delete (principalref->sitesRefs)[std::stoi(straux.substr(4, 4))];                    //Deleta o elemento
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
    }
    catch (InvalidKey &ex)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",ex.what());
        messageBox.setFixedSize(500,200);
    }
}
