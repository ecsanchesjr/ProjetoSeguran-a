#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QFrame>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <iostream>
#include <string>
#include <DAO.hpp>
namespace Ui {
class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();

private:
    Ui::Principal *ui;
    QLineEdit* criaCampo(QString texto, QString nomeObj);
    QPushButton *criaBotao(QString texto, QString nomeObj,int typeCampo);
    QFrame* criaFrame(QVBoxLayout *qlayout);
    QFrame* criaFrame(QHBoxLayout *qlayout);
    void setCampos(QVBoxLayout*, pair<string,string>, int  i);
    void setBotoes(QHBoxLayout*,int i);
    void fillBoxes(QVBoxLayout*,int);
    std::vector<QLineEdit*> sitesRefs;
    std::vector<QLineEdit*> nicksRefs;
    std::vector<QLineEdit*> senhasRefs;
    std::vector<QFrame*> cFramesRefs;
    std::vector<QFrame*> bFramesRefs;
    std::vector<QVBoxLayout*>paneRefs;

private slots:
    void goHandler();
    void editHandler();
    void removeHandler();
    void on_pushButton_2_clicked();
};

#endif // PRINCIPAL_H
