#ifndef PASSDIALOG_H
#define PASSDIALOG_H

#include <QWidget>
#include <QCloseEvent>
#include <headers/login.h>
class addEntry;
class Principal;
namespace Ui
{
class passDialog;
}

class passDialog : public QWidget
{
    Q_OBJECT

  public:
    explicit passDialog(QWidget *parent = 0, int = 0);

    //construtor para quando é chamada pela addentry
    explicit passDialog(QWidget *parent = 0, QWidget *addEntryWin = 0, string = "", string = "", string = "");
    ~passDialog();

  private:
    Ui::passDialog *ui;
    Principal *principalref;
    addEntry *addEntryPtr;
    std::string site, nick, pass;
  private slots:
    void remove();
    void modify();
    void go();
    void newEntry();
    void deleteUser();
    void closeEvent(QCloseEvent *);
};

#endif // PASSDIALOG_H
