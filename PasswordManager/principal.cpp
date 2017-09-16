#include "principal.h"
#include "ui_principal.h"
#include <QPushButton>
#include <QLineEdit>
#include <iostream>
Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    for(int i=0;i<100;i++){
        QVBoxLayout *templ= new QVBoxLayout();
        QVBoxLayout *templ2= new QVBoxLayout();
        QFrame *frame= new QFrame;

        QLineEdit *lsite=new QLineEdit("Site do batata2");
        lsite->setMaximumWidth(500);
        templ->addWidget(lsite);
        //Teste Commit
        QLineEdit *lnick=new QLineEdit("Nick do batata");
        lnick->setMaximumWidth(500);
        templ->addWidget(lnick);


        QLineEdit *lpass=new QLineEdit("Senha do batata");
        lpass->setMaximumWidth(500);
        templ->addWidget(lpass);

        QPushButton *pbutton= new QPushButton("Go");
        pbutton->setMaximumWidth(100);
        templ->addWidget(pbutton);
        templ->setAlignment(templ,Qt::AlignLeft);
        templ->setMargin(20);
        frame->setLayout(templ);
        frame->setFrameShape(QFrame::Box);
        std::cout<<frame->frameShape()<<std::endl;
        frame->setLineWidth(1);
        frame->setMaximumWidth(500);
        frame->setMaximumHeight(200);
        templ2->addWidget(frame);
        templ2->setMargin(10);
        ui->gridLayout_3->setMargin(3);
        if(i%2==0){
            ui->gridLayout_3->addLayout(templ2,i,0,Qt::AlignCenter);
        }else{
            ui->gridLayout_3->addLayout(templ2,i-1,1,Qt::AlignCenter);
        }
    }
}

Principal::~Principal()
{
    delete ui;
}
