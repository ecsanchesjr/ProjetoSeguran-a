#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QFrame>
#include <iostream>
#include <DAO.hpp>
#include <principal.h>
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
};

#endif // ADDENTRY_H
