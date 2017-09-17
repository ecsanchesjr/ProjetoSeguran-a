#include "addentry.h"
#include "ui_addentry.h"
#include <utility>


addEntry::addEntry(QWidget *parent) :
    QFrame(),
    ui(new Ui::addEntry)
{
    ui->setupUi(this);
    principalref= (Principal*)parent;
}

addEntry::~addEntry()
{
    delete ui;
}

void addEntry::on_pushButton_clicked()
{
    pair<string, bool> returnQInput=principalref->askPassword();
    if(returnQInput.second){
        std::cout<<"Site:" << ui->lineEdit->text().toStdString()<<std::endl;
        std::cout<<"Nick:" << ui->lineEdit_2->text().toStdString()<<std::endl;
        std::cout<<"Senha:" << ui->lineEdit_3->text().toStdString()<<std::endl;
        std::string user = principalref->getUsername();
        std::string site=ui->lineEdit->text().toStdString();
        std::string nick=ui->lineEdit_2->text().toStdString();
        std::string senha=ui->lineEdit_3->text().toStdString();
        std::string key=returnQInput.first;
        try{
            principalref->getDao()->createNewEntry(site,nick,senha,key);
            principalref->redrawAll();
            this->hide();
        }catch(InvalidKey &ex){
            QMessageBox messageBox;
            messageBox.critical(0,"Error",ex.what());
            messageBox.setFixedSize(500,200);
        }
    }else{
        // nothing
    }
}
