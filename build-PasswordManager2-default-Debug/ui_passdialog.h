/********************************************************************************
** Form generated from reading UI file 'passdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSDIALOG_H
#define UI_PASSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_passDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *passDialog)
    {
        if (passDialog->objectName().isEmpty())
            passDialog->setObjectName(QStringLiteral("passDialog"));
        passDialog->setWindowModality(Qt::WindowModal);
        passDialog->resize(400, 152);
        verticalLayout = new QVBoxLayout(passDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(passDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 60));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(passDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(passDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(passDialog);

        QMetaObject::connectSlotsByName(passDialog);
    } // setupUi

    void retranslateUi(QWidget *passDialog)
    {
        passDialog->setWindowTitle(QApplication::translate("passDialog", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("passDialog", "Digite sua senha para confirmar a a\303\247\303\243o:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("passDialog", "Confirmar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class passDialog: public Ui_passDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSDIALOG_H
