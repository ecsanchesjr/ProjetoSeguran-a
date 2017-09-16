#include "principal.h"
#include "ui_principal.h"
Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    std::string name="username2";
    std::string pass="text";
    DAO dao(name,pass);
    int i=0;
    vector<pair<string,string>> infos =  dao.getNamesAndLogin(pass);

    for(pair<string,string> it : infos){
        QVBoxLayout *templ= new QVBoxLayout();
        QVBoxLayout *templ2= new QVBoxLayout();

        QString tempstr="Site do batata";
        tempstr.append(QString::number(i));
        QLineEdit* temp=criaCampo(QString::fromStdString(it.first),tempstr);
        sitesRefs.push_back(temp);
        templ->addWidget(temp);

        tempstr="Nick do batata";
        tempstr.append(QString::number(i));
        temp=criaCampo(QString::fromStdString(it.second),tempstr);
        nicksRefs.push_back(temp);
        templ->addWidget(temp);

        tempstr="Senha do batata";
        tempstr.append(QString::number(i));
        temp=criaCampo(tempstr,tempstr);
        senhasRefs.push_back(temp);
        templ->addWidget(temp);

        tempstr="Go";
        tempstr.append(QString::number(i));
        templ->addWidget(criaBotao("Go",tempstr));

        templ->setAlignment(templ,Qt::AlignLeft);
        templ->setMargin(20);

        templ2->addWidget(criaFrame(templ));
        templ2->setMargin(10);

        ui->gridLayout_3->setMargin(3);
        fillBoxes(templ2,i);
        i++;
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
    std::string straux=((QPushButton*)buttonWidget)->objectName().toStdString();
    std::cout<<"Você cliclou no pane "<< straux.substr(2,2)<<endl;
    std::cout<<"O texto no site desse pane é " <<sitesRefs[std::stoi(straux.substr(2,2))]->text().toStdString()<<std::endl;
    std::cout<<"O texto no nick desse pane é " <<nicksRefs[std::stoi(straux.substr(2,2))]->text().toStdString()<<std::endl;
    std::cout<<"O texto na senha desse pane é " <<senhasRefs[std::stoi(straux.substr(2,2))]->text().toStdString()<<std::endl;
}
