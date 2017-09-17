#include "principal.h"
#include "ui_principal.h"
#include <login.h>
#include <addentry.h>
#include "passdialog.h"
Principal::Principal(QWidget *parent) : QMainWindow(parent),
                                        ui(new Ui::Principal)
{
    ui->setupUi(this);
    username = ((login *)parent)->getUsername();
    password = ((login *)parent)->getPassword();
    dao = ((login *)parent)->getDao();
    std::cout << username << std::endl;
    std::cout << password << std::endl;
    drawElements();
}
void Principal::clearAll()
{
    int size = paneRefs.size();
    for (int i = 0; i < size; i++)
    {
        delete sitesRefs[i];
        delete nicksRefs[i];
        delete senhasRefs[i];
        delete paneRefs[i];
        delete cFramesRefs[i];
        delete bFramesRefs[i];
    }
}

void Principal::drawElements()
{
    paneRefs.clear();
    cFramesRefs.clear();
    bFramesRefs.clear();
    sitesRefs.clear();
    nicksRefs.clear();
    senhasRefs.clear();
    try
    {
        int i = 0; //Contador para auxiliar o preenchimento
        vector<pair<string, string>> infos = dao->getNamesAndLogin(password);
        for (pair<string, string> it : infos)
        {
            //Layouts temporários para organização
            QVBoxLayout *templ = new QVBoxLayout();  //Layout dos campos
            QVBoxLayout *templ2 = new QVBoxLayout(); //Layout dos campos + botões
            QHBoxLayout *templ3 = new QHBoxLayout(); //Layout dos botões
            //Chamada para criar os campos
            setCampos(templ, it, i);
            //Criação dos botões
            setBotoes(templ3, i);
            templ->setAlignment(templ, Qt::AlignLeft); //Alinhamento a esquerda no layout temporário
            templ->setMargin(20);

            templ2->addWidget(criaFrame(templ));  //Adiciona o frame com os campos
            templ2->addWidget(criaFrame(templ3)); //Adiciona o frame com os botões
            templ2->setMargin(10);
            paneRefs.push_back(templ2);

            ui->gridLayout->setMargin(10);
            fillBoxes(templ2, i); //Adiciona os layouts criados no grid
            i++;
        }
    }
    catch (UserNotFound &ex)
    {
        cout << ex.what() << endl;
        QMessageBox messageBox;
        messageBox.critical(0, "Error", ex.what());
        messageBox.setFixedSize(500, 200);
    }
}

void Principal::setBotoes(QHBoxLayout *qlayout, int i)
{
    //Criação dos botões
    QString tempstr = "Pane";
    tempstr.append(QString::number(i));
    qlayout->addWidget(criaBotao("Go", tempstr, 1));
    qlayout->addWidget(criaBotao("Edit", tempstr, 2));
    qlayout->addWidget(criaBotao("Remove", tempstr, 3));
}

void Principal::setCampos(QVBoxLayout *qlayout, pair<string, string> nickPass, int i)
{
    //Criação do campo do site
    QString tempstr = "SitePane";
    tempstr.append(QString::number(i));
    QLineEdit *temp = criaCampo(QString::fromStdString(nickPass.first), tempstr);
    temp->setReadOnly(true);
    sitesRefs.push_back(temp); //Armazena num vetor para indexação e acesso em tempo constante
    qlayout->addWidget(temp);  //Adiciona ao layout

    //Criação do campo do nick
    tempstr = "NickPane";
    tempstr.append(QString::number(i));
    temp = criaCampo(QString::fromStdString(nickPass.second), tempstr);
    nicksRefs.push_back(temp);
    qlayout->addWidget(temp);

    //Criaçao do campo de senha
    tempstr = "SenhaPane";
    tempstr.append(QString::number(i));
    temp = criaCampo("********", tempstr);
    senhasRefs.push_back(temp);
    qlayout->addWidget(temp);
}

void Principal::fillBoxes(QVBoxLayout *qlayout, int i)
{
    if (i % 2 == 0)
    {
        ui->gridLayout->addLayout(qlayout, i, 0, Qt::AlignCenter);
    }
    else
    {
        ui->gridLayout->addLayout(qlayout, i - 1, 1, Qt::AlignCenter);
    }
}

QFrame *Principal::criaFrame(QVBoxLayout *qlayout)
{
    QFrame *frame = new QFrame();
    frame->setLayout(qlayout);
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(1);
    frame->setMaximumWidth(500);
    frame->setMaximumHeight(200);
    cFramesRefs.push_back(frame);
    return frame;
}
QFrame *Principal::criaFrame(QHBoxLayout *qlayout)
{
    QFrame *frame = new QFrame();
    frame->setLayout(qlayout);
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(1);
    frame->setMaximumWidth(500);
    frame->setMaximumHeight(200);
    bFramesRefs.push_back(frame);
    return frame;
}
QLineEdit *Principal::criaCampo(QString texto, QString nomeObj)
{
    QLineEdit *line = new QLineEdit(texto);
    line->setObjectName(nomeObj);
    return line;
}
QPushButton *Principal::criaBotao(QString texto, QString nomeObj, int typeCampo)
{
    //Tipo 1 = go Tipo 2 = edit Tipo3 = remove
    QPushButton *button = new QPushButton(texto);
    button->setObjectName(nomeObj);
    button->setCheckable(true);
    switch (typeCampo)
    {
    case 1:
        connect(button, SIGNAL(clicked(bool)), this, SLOT(goHandler()));
        break;

    case 2:
        connect(button, SIGNAL(clicked(bool)), this, SLOT(editHandler()));
        break;

    case 3:
        connect(button, SIGNAL(clicked(bool)), this, SLOT(removeHandler()));
        break;
    }
    button->setMaximumWidth(100);
    return button;
}

Principal::~Principal()
{
    delete ui;
}
//Substituir corpo dos actions pelas ações com a cript + o xml
void Principal::goHandler() //Action ao clicar no botão go
{
    QWidget *buttonWidget = qobject_cast<QWidget *>(sender());
    if (!buttonWidget)
        return;
    
    indexPane = ((QPushButton *)buttonWidget)->objectName().toStdString();

    passDialog* pD= new passDialog(this,1);
    pD->show();
}

void Principal::editHandler()
{ //Action ao clicar no botão edit
    QWidget *buttonWidget = qobject_cast<QWidget *>(sender());
    if (!buttonWidget)
        return;

    indexPane = ((QPushButton *)buttonWidget)->objectName().toStdString();

    passDialog *pD = new passDialog(this,3);
    pD->show();
}

void Principal::removeHandler()
{ //Action  ao clicar no botão remove
    QWidget *buttonWidget = qobject_cast<QWidget *>(sender());
    if (!buttonWidget)
        return;
    indexPane = ((QPushButton *)buttonWidget)->objectName().toStdString();
    std::cout << "Você removeu o pane " << indexPane.substr(4, 4) << endl;
    //Remove a entrada no arquivo
    passDialog* pD= new passDialog(this,2);
    pD->show();
}
void Principal::redrawAll()
{
    clearAll();
    drawElements();
}

void Principal::on_pushButton_2_clicked()
{
    std::cout << "Adicionar nova entrada" << std::endl;
    addEntry *ae = new addEntry(this);
    ae->show();
}

std::string Principal::getUsername()
{
    return username;
}
std::string Principal::getPassword()
{
    return password;
}

DAO *Principal::getDao()
{
    return dao;
}

 void Principal::displayInvalidPass(const string &error){
    QMessageBox messageBox;
    messageBox.critical(0,"Error",error.c_str());
    messageBox.setFixedSize(500,200);    
}

