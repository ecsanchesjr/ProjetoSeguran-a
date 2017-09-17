#include "addentry.h"
#include "ui_addentry.h"
#include "passdialog.h"
#include <utility>

addEntry::addEntry(QWidget *parent) : QFrame(),
                                      ui(new Ui::addEntry)
{
    ui->setupUi(this);
    principalref = (Principal *)parent;
}

addEntry::~addEntry()
{
    delete ui;
}

void addEntry::on_pushButton_clicked()
{
    passDialog *pD = new passDialog(principalref,this,
                                    ui->lineEdit->text().toStdString(),
                                    ui->lineEdit_2->text().toStdString(),
                                    ui->lineEdit_3->text().toStdString());
    pD->show();
}

void addEntry::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    
    //memory leak aqui, precisamos deletar, mas ele fecha o programa todo, why?
    //delete this;

}