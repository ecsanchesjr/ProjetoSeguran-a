#include "addentry.h"
#include "ui_addentry.h"
#include "passdialog.h"
#include <utility>
#include <QDesktopWidget>

addEntry::addEntry(QWidget *parent) : QFrame(),
                                      ui(new Ui::addEntry)
{
    ui->setupUi(this);
    principalref = (Principal *)parent;
    //Ajuste da tela
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    QDesktopWidget btt;
    int screenWidth = btt.screen()->width();
    int screenHeight = btt.screen()->height();
    this->setGeometry((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2), width, height);
}

addEntry::~addEntry()
{
    delete ui;
}

void addEntry::on_pushButton_clicked()
{
    if (ui->lineEdit->text().toStdString().length() != 0 && ui->lineEdit_2->text().toStdString().length() != 0 && ui->lineEdit_3->text().toStdString().length() != 0)
    {
        passDialog *pD = new passDialog(principalref, this,
                                        ui->lineEdit->text().toStdString(),
                                        ui->lineEdit_2->text().toStdString(),
                                        ui->lineEdit_3->text().toStdString());
        pD->show();
    }
    else
    {
        principalref->displayErrorMessage("Empty Input Field");
    }
}

void addEntry::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    delete ui;
}
