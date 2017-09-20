#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QFrame>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <string>
#include <DAO.hpp>
#include <login.h>
#include <utility>
#include "passdialog.h"
#include "addentry.h"
#include "login.h"
#include "changepassword.h"
class passDialog;
class addEntry;
class login;
class ChangePassword;
namespace Ui {
class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    void redrawAll();
    ~Principal();



    
    //GAMBI DO CARALHO
    void setPassword(string);







    std::string getUsername();
    std::string getPassword();
    DAO* getDao();
    pair<string, bool> askPassword();
    std::vector<QLineEdit*> sitesRefs;
    std::vector<QLineEdit*> nicksRefs;
    std::vector<QLineEdit*> senhasRefs;
    std::vector<QFrame*> cFramesRefs;
    std::vector<QFrame*> bFramesRefs;
    std::vector<QVBoxLayout*>paneRefs;
    std::string indexPane;
    void displayErrorMessage(const string&);
    passDialog *pD = nullptr;
    ChangePassword *cP = nullptr;
    addEntry *ae= nullptr;
    void closeFromLogin();
    login* loginref;
private:
    Ui::Principal *ui;
    QLineEdit* criaCampo(QString texto, QString nomeObj);
    QPushButton *criaBotao(QString texto, QString nomeObj,int typeCampo);
    QFrame* criaFrame(QVBoxLayout *qlayout);
    QFrame* criaFrame(QHBoxLayout *qlayout);
    void setCampos(QVBoxLayout*, pair<string,string>, int  i);
    void setBotoes(QHBoxLayout*,int i);
    void fillBoxes(QVBoxLayout*,int);
    void drawElements();
    void clearAll();
    std::string username;
    std::string password;
    DAO* dao= nullptr;
private slots:
    void goHandler();
    void editHandler();
    void removeHandler();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void closeEvent(QCloseEvent *);
    void on_pushButton_4_clicked();
};

#endif // PRINCIPAL_H
