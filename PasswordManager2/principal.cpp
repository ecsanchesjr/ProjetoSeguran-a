#include "principal.h"
#include "ui_principal.h"
#include <QPushButton>
#include <QLineEdit>
#include <iostream>
#include <string>
#include <DAO.hpp>
Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    std::string name="username2";
    std::string pass="text";
    DAO dao(name,pass);
    for(int i=0;i<100;i++){
        QVBoxLayout *templ= new QVBoxLayout();
        QVBoxLayout *templ2= new QVBoxLayout();

        QString tempstr="Site do batata";
        tempstr.append(QString::number(i));
        templ->addWidget(criaCampo(tempstr,tempstr));

        tempstr="Nick do batata";
        tempstr.append(QString::number(i));
        templ->addWidget(criaCampo(tempstr,tempstr));

        tempstr="Senha do batata";
        tempstr.append(QString::number(i));
        templ->addWidget(criaCampo(tempstr,tempstr));

        tempstr="Go";
        tempstr.append(QString::number(i));
        templ->addWidget(criaBotao("Go",tempstr));

        templ->setAlignment(templ,Qt::AlignLeft);
        templ->setMargin(20);

        templ2->addWidget(criaFrame(templ));
        templ2->setMargin(10);

        ui->gridLayout_3->setMargin(3);
        fillBoxes(templ2,i);
    }
}
void Principal::fillBoxes(QVBoxLayout* qlayout, int i){
    if(i%2==0){
        ui->gridLayout_3->addLayout(qlayout,i,0,Qt::AlignCenter);
    }else{
        ui->gridLayout_3->addLayout(qlayout,i-1,1,Qt::AlignCenter);
    }
}

QFrame* Principal::criaFrame(QVBoxLayout* qlayout){
    QFrame *frame = new QFrame();
    frame->setLayout(qlayout);
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(1);
    frame->setMaximumWidth(500);
    frame->setMaximumHeight(200);
    return frame;
}

QLineEdit* Principal::criaCampo(QString texto, QString nomeObj){
    QLineEdit *line= new QLineEdit(texto);
    line->setObjectName(nomeObj);
    return line;
}
QPushButton* Principal::criaBotao(QString texto, QString nomeObj){
    QPushButton* button=new QPushButton(texto);
    button->setObjectName(nomeObj);
    button->setCheckable(true);
    connect(button, SIGNAL (clicked(bool)), this, SLOT (buttonHandler()));
    button->setMaximumWidth(50);
    return button;
}

Principal::~Principal()
{
    delete ui;
}

void Principal::buttonHandler()
{

    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;
    std::cout<<((QPushButton*)buttonWidget)->objectName().toStdString()<<std::endl;
}
