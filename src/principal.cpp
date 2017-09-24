#include "headers/principal.h"
#include "ui_principal.h"
#include <headers/login.h>
#include <headers/addentry.h>
#include <QDesktopWidget>

Principal::Principal(QWidget *parent) : QMainWindow(parent),
                                        ui(new Ui::Principal)
{
    ui->setupUi(this);
    smap = new QSignalMapper(this);
    username = ((login *)parent)->getUsername();
    passwordBuffer = ((login *)parent)->getPassword();
    dao = ((login *)parent)->getDao();
    loginref = ((login *)parent);
    loginref->principalRef = this;
    loginref->clearFields();
    ui->label->setText("Welcome " + QString::fromStdString(username));
    //------------
    drawElements();
    //Ajuste da tela
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    QDesktopWidget btt;
    int screenWidth = btt.screen()->width();
    int screenHeight = btt.screen()->height();
    this->setGeometry((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2), width, height);
}
void Principal::clearAll()
{
    int size = paneRefs.size();
    for (int i = 0; i < size; i++)
    {
        delete sitesRefs[i];
        sitesRefs[i] = nullptr;
        delete nicksRefs[i];
        nicksRefs[i] = nullptr;
        delete senhasRefs[i];
        senhasRefs[i] = nullptr;
        delete paneRefs[i];
        paneRefs[i] = nullptr;
        delete cFramesRefs[i];
        cFramesRefs[i] = nullptr;
        delete bFramesRefs[i];
        bFramesRefs[i] = nullptr;
    }
    paneRefs.clear();
    cFramesRefs.clear();
    bFramesRefs.clear();
    sitesRefs.clear();
    nicksRefs.clear();
    senhasRefs.clear();
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
        //cout << "get names and login" << endl;
        try{
        vector<pair<string, string>> infos = dao->getNamesAndLogin(passwordBuffer);
        infosBuffer=infos;
        }
        catch(InvalidKey &ex){

        }

        passwordBuffer="";
        for (pair<string, string> it : infosBuffer)
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
            smartPadding(templ2,i);

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
    catch (FileIntegrityNotAssured &ex)
    {
        displayErrorMessage(ex.what());
    }
}
void Principal::smartPadding(QVBoxLayout *qlayout,int i){
    if(this->frameGeometry().width()>=1280){
        fillBoxes4(qlayout, i); //Adiciona os layouts criados no grid
    }
    else if(this->frameGeometry().width()>=960){
        fillBoxes3(qlayout, i); //Adiciona os layouts criados no grid
    }
    else{
        fillBoxes2(qlayout, i); //Adiciona os layouts criados no grid
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
    QString tempstr = "";
    QLineEdit *temp = criaCampo(QString::fromStdString(nickPass.first), QString::fromStdString(nickPass.first));
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
    temp = criaCampo("", tempstr);
    temp->setPlaceholderText("Press the GO button to see password");
    senhasRefs.push_back(temp);
    qlayout->addWidget(temp);
}

void Principal::fillBoxes2(QVBoxLayout *qlayout, int i)
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

void Principal::fillBoxes3(QVBoxLayout *qlayout, int i)
{
    if (i % 3 == 0)
    {
        ui->gridLayout->addLayout(qlayout, (int)(i/3),0, Qt::AlignCenter);

    }
    else if((i-1) % 3 == 0)
    {
        ui->gridLayout->addLayout(qlayout, (int)(i/3),1, Qt::AlignCenter);

    }
    else if((i-2)%3==0){
        ui->gridLayout->addLayout(qlayout, (int)(i/3),2, Qt::AlignCenter);
    }
}

void Principal::fillBoxes4(QVBoxLayout *qlayout, int i)
{
    if (i % 4 == 0)
    {
        ui->gridLayout->addLayout(qlayout, (int)(i/4),0, Qt::AlignCenter);
    }
    else if((i-1) % 4 == 0)
    {
        ui->gridLayout->addLayout(qlayout, (int)(i/4),1, Qt::AlignCenter);
    }
    else if((i-2)%4==0){
        ui->gridLayout->addLayout(qlayout, (int)(i/4),3, Qt::AlignCenter);
    }
    else if((i-3)%4==0){
        ui->gridLayout->addLayout(qlayout, (int)(i/4),4, Qt::AlignCenter);
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
    for(unsigned int i=0;i<timerrefs.size();i++){
        timerrefs[i]->stop();
        delete timerrefs[i];
    }
    clearAll();
    delete dao;
    delete pD;
    delete ui;
    delete cP;
    std::cout << "Destruindo Principal " << std::endl;
}
//Substituir corpo dos actions pelas ações com a cript + o xml
void Principal::goHandler() //Action ao clicar no botão go
{
    QWidget *buttonWidget = qobject_cast<QWidget *>(sender());
    if (!buttonWidget)
        return;

    indexPane = ((QPushButton *)buttonWidget)->objectName().toStdString();
    delete pD;
    pD = new passDialog(this, 1);
    pD->show();
}

void Principal::editHandler()
{ //Action ao clicar no botão edit
    QWidget *buttonWidget = qobject_cast<QWidget *>(sender());
    if (!buttonWidget)
        return;

    indexPane = ((QPushButton *)buttonWidget)->objectName().toStdString();
    delete pD;
    pD = new passDialog(this, 3);
    pD->show();
}

void Principal::removeHandler()
{ //Action  ao clicar no botão remove
    QWidget *buttonWidget = qobject_cast<QWidget *>(sender());
    if (!buttonWidget)
        return;
    indexPane = ((QPushButton *)buttonWidget)->objectName().toStdString();
    //Remove a entrada no arquivo
    delete pD;
    pD = new passDialog(this, 2);
    pD->show();
}
void Principal::redrawAll()
{
    clearAll();
    drawElements();
}

void Principal::on_pushButton_2_clicked() //Adicionar nova entrada
{
    delete ae;
    ae = nullptr;
    ae = new addEntry(this);
    ae->show();
}

std::string Principal::getUsername()
{
    return username;
}
std::string Principal::getPassword()
{
    return passwordBuffer;
}

DAO *Principal::getDao()
{
    return dao;
}

void Principal::displayErrorMessage(const string &error)
{
    QMessageBox messageBox;
    messageBox.critical(0, "Error", error.c_str());
    messageBox.setFixedSize(500, 200);
}

void Principal::on_pushButton_clicked() //Sair
{
    for(unsigned int i=0;i<timerrefs.size();i++){
        timerrefs[i]->stop();
        delete timerrefs[i];
    }
    timerrefs.clear();
    clearAll();
    delete dao;
    delete pD;
    delete ae;
    delete cP;
    pD = nullptr;
    ae = nullptr;
    dao = nullptr;
    cP = nullptr;
    loginref->show();
    this->hide();
}

void Principal::on_pushButton_3_clicked() //Deletar o usuário
{
    delete pD;
    pD = new passDialog(this, 4);
    pD->show();
}

void Principal::setPassword(string pass)
{
    this->passwordBuffer = pass;
}

void Principal::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    delete pD;
    pD = nullptr;
    delete ae;
    ae = nullptr;
    delete cP;
    cP = nullptr;
    loginref->goingToClose = true;
    delete loginref;
}

void Principal::closeFromLogin()
{
    this->hide();
    delete pD;
    pD = nullptr;
    delete ae;
    ae = nullptr;
    delete cP;
    cP = nullptr;
}

void Principal::on_pushButton_4_clicked() //Altera a senha
{
    delete cP;
    cP = new ChangePassword(this);
    cP->show();
}

void Principal::resizeEvent(QResizeEvent *event){
    event->ignore();
    std::vector<QString> sitesRefsBuf;
    std::vector<QString> nicksRefsBuf;
    std::vector<QString> senhasRefsBuf;
    unsigned int i=0;
    for(i=0;i<sitesRefs.size();i++){
        sitesRefsBuf.push_back(sitesRefs[i]->text());
        nicksRefsBuf.push_back(nicksRefs[i]->text());
        senhasRefsBuf.push_back(senhasRefs[i]->text());
    }
    redrawAll();
    for(i=0;i<sitesRefs.size();i++){
        sitesRefs[i]->setText(sitesRefsBuf[i]);
        nicksRefs[i]->setText(nicksRefsBuf[i]);
        senhasRefs[i]->setText(senhasRefsBuf[i]);
    }
}


void Principal::on_pushButton_5_clicked()
{
    std::cout<<"Edit All"<<std::endl;
    delete pD;
    pD=new passDialog(this,5);
    pD->show();
}

void Principal::timerHandler(int index)
{
   senhasRefs[index]->clear();
}

