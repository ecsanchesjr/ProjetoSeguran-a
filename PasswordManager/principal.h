#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QFrame>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
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
    QPushButton *criaBotao(QString texto, QString nomeObj);
    QFrame* criaFrame(QVBoxLayout *qlayout);
    void fillBoxes(QVBoxLayout*,int);
private slots:
    void buttonHandler();
};

#endif // PRINCIPAL_H
