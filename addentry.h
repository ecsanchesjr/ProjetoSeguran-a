#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QFrame>
#include <iostream>
#include <DAO.hpp>
#include <QCloseEvent>
class Principal;
namespace Ui {
class addEntry;
}

class addEntry : public QFrame
{
    Q_OBJECT

public:
    explicit addEntry(QWidget *parent = 0);
    ~addEntry();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addEntry *ui;
    Principal* principalref;
    void closeEvent(QCloseEvent*);
};

#endif // ADDENTRY_H
