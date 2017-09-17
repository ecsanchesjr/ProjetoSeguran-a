/********************************************************************************
** Form generated from reading UI file 'addentry.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDENTRY_H
#define UI_ADDENTRY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_addEntry
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;

    void setupUi(QFrame *addEntry)
    {
        if (addEntry->objectName().isEmpty())
            addEntry->setObjectName(QStringLiteral("addEntry"));
        addEntry->resize(400, 301);
        addEntry->setFrameShape(QFrame::StyledPanel);
        addEntry->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(addEntry);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(addEntry);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(addEntry);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        label_2 = new QLabel(addEntry);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(addEntry);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        label_3 = new QLabel(addEntry);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        lineEdit_3 = new QLineEdit(addEntry);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        verticalLayout->addWidget(lineEdit_3);

        pushButton = new QPushButton(addEntry);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(addEntry);

        QMetaObject::connectSlotsByName(addEntry);
    } // setupUi

    void retranslateUi(QFrame *addEntry)
    {
        addEntry->setWindowTitle(QApplication::translate("addEntry", "Frame", Q_NULLPTR));
        label->setText(QApplication::translate("addEntry", "Site:", Q_NULLPTR));
        label_2->setText(QApplication::translate("addEntry", "Nick:", Q_NULLPTR));
        label_3->setText(QApplication::translate("addEntry", "Senha:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("addEntry", "Adicionar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addEntry: public Ui_addEntry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDENTRY_H
