#include "addentry.h"
#include "ui_addentry.h"

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
    std::cout<<"Site:" << ui->lineEdit->text().toStdString()<<std::endl;
    std::cout<<"Nick:" << ui->lineEdit_2->text().toStdString()<<std::endl;
    std::cout<<"Senha:" << ui->lineEdit_3->text().toStdString()<<std::endl;
    std::string user = "username2";
    std::string site=ui->lineEdit->text().toStdString();
    std::string nick=ui->lineEdit_2->text().toStdString();
    std::string senha=ui->lineEdit_3->text().toStdString();
    std::string key="";
    DAO dao(user,user);
    dao.createNewEntry(site,nick,senha,key);
    principalref->redrawAll();
}
