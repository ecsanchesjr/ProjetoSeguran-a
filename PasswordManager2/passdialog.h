#ifndef PASSDIALOG_H
#define PASSDIALOG_H

#include <QWidget>
#include <principal.h>
#include <QCloseEvent>
namespace Ui {
class passDialog;
}

class passDialog : public QWidget
{
    Q_OBJECT

public:
    explicit passDialog(QWidget *parent = 0);
    ~passDialog();

private:
    Ui::passDialog *ui;
    Principal* principalref;

private slots:
    void remove();
    void go();
    void closeEvent(QCloseEvent*);
};

#endif // PASSDIALOG_H
