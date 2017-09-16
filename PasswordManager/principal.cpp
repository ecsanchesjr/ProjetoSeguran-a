#include "principal.h"
#include "ui_principal.h"
#include <QPushButton>
#include <QLineEdit>

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    for(int i=0;i<10;i++){
        QVBoxLayout *templ= new QVBoxLayout();

        QLineEdit *lsite=new QLineEdit("Site do batata");
        lsite->setMaximumWidth(200);
        templ->addWidget(lsite);

        QLineEdit *lnick=new QLineEdit("Nick do batata");
        lnick->setMaximumWidth(200);
        templ->addWidget(lnick);


        QLineEdit *lpass=new QLineEdit("Senha do batata");
        lpass->setMaximumWidth(200);
        templ->addWidget(lpass);

        QPushButton *pbutton= new QPushButton("Go");
        pbutton->setMaximumWidth(50);
        templ->addWidget(pbutton);
        templ->setAlignment(templ,Qt::AlignLeft);
        ui->verticalLayout->addLayout(templ);
    }
}

Principal::~Principal()
{
    delete ui;
}
