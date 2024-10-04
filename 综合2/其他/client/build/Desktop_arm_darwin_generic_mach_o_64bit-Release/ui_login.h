/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPwd;
    QLineEdit *lineEditPwd;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BtnSignUp;
    QPushButton *BtnSignIn;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(232, 144);
        gridLayout = new QGridLayout(Login);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelName = new QLabel(Login);
        labelName->setObjectName("labelName");

        horizontalLayout->addWidget(labelName);

        lineEditName = new QLineEdit(Login);
        lineEditName->setObjectName("lineEditName");

        horizontalLayout->addWidget(lineEditName);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelPwd = new QLabel(Login);
        labelPwd->setObjectName("labelPwd");

        horizontalLayout_2->addWidget(labelPwd);

        lineEditPwd = new QLineEdit(Login);
        lineEditPwd->setObjectName("lineEditPwd");
        lineEditPwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEditPwd);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);

        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        BtnSignUp = new QPushButton(Login);
        BtnSignUp->setObjectName("BtnSignUp");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BtnSignUp->sizePolicy().hasHeightForWidth());
        BtnSignUp->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(BtnSignUp);

        BtnSignIn = new QPushButton(Login);
        BtnSignIn->setObjectName("BtnSignIn");
        sizePolicy.setHeightForWidth(BtnSignIn->sizePolicy().hasHeightForWidth());
        BtnSignIn->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(BtnSignIn);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 2);
        gridLayout->setRowStretch(2, 1);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        labelName->setText(QCoreApplication::translate("Login", "Username", nullptr));
        labelPwd->setText(QCoreApplication::translate("Login", "Password", nullptr));
        BtnSignUp->setText(QCoreApplication::translate("Login", "Sign Up", nullptr));
        BtnSignIn->setText(QCoreApplication::translate("Login", "Sign In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
