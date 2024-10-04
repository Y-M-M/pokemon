/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelUser;
    QHBoxLayout *horizontalLayout;
    QLabel *labelWho;
    QPushButton *BtnBadge;
    QComboBox *CbxUser;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelNum;
    QLabel *labelNumBadge;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelAdv;
    QLabel *labelAdvBadge;
    QLabel *labelInfo;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QPushButton *BtnLoginOut;
    QSpacerItem *verticalSpacer;
    QPushButton *BtnOnline;
    QSpacerItem *verticalSpacer_2;
    QPushButton *BtnAllUsers;
    QSpacerItem *verticalSpacer_3;
    QPushButton *BtnUpgrade;
    QSpacerItem *verticalSpacer_4;
    QPushButton *BtnDuel;
    QSpacerItem *verticalSpacer_6;
    QPushButton *BtnRate;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *showInfo;
    QListWidget *listWidgetUsers;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelServer;
    QComboBox *comboBox;
    QPushButton *BtnConfirm;
    QLabel *labelSPkm;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(702, 399);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setEnabled(true);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_5 = new QVBoxLayout(centralWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelUser = new QLabel(centralWidget);
        labelUser->setObjectName("labelUser");

        verticalLayout_3->addWidget(labelUser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        labelWho = new QLabel(centralWidget);
        labelWho->setObjectName("labelWho");
        labelWho->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(labelWho);

        BtnBadge = new QPushButton(centralWidget);
        BtnBadge->setObjectName("BtnBadge");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BtnBadge->sizePolicy().hasHeightForWidth());
        BtnBadge->setSizePolicy(sizePolicy);
        BtnBadge->setCheckable(true);

        horizontalLayout->addWidget(BtnBadge);

        CbxUser = new QComboBox(centralWidget);
        CbxUser->setObjectName("CbxUser");

        horizontalLayout->addWidget(CbxUser);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        labelNum = new QLabel(centralWidget);
        labelNum->setObjectName("labelNum");

        horizontalLayout_4->addWidget(labelNum);

        labelNumBadge = new QLabel(centralWidget);
        labelNumBadge->setObjectName("labelNumBadge");

        horizontalLayout_4->addWidget(labelNumBadge);

        horizontalLayout_4->setStretch(0, 10);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        labelAdv = new QLabel(centralWidget);
        labelAdv->setObjectName("labelAdv");

        horizontalLayout_5->addWidget(labelAdv);

        labelAdvBadge = new QLabel(centralWidget);
        labelAdvBadge->setObjectName("labelAdvBadge");

        horizontalLayout_5->addWidget(labelAdvBadge);

        horizontalLayout_5->setStretch(0, 10);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(verticalLayout_4);

        labelInfo = new QLabel(centralWidget);
        labelInfo->setObjectName("labelInfo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelInfo->sizePolicy().hasHeightForWidth());
        labelInfo->setSizePolicy(sizePolicy1);
        labelInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_3->addWidget(labelInfo);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(3, 6);

        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        BtnLoginOut = new QPushButton(centralWidget);
        BtnLoginOut->setObjectName("BtnLoginOut");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(BtnLoginOut->sizePolicy().hasHeightForWidth());
        BtnLoginOut->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(BtnLoginOut);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        BtnOnline = new QPushButton(centralWidget);
        BtnOnline->setObjectName("BtnOnline");
        sizePolicy.setHeightForWidth(BtnOnline->sizePolicy().hasHeightForWidth());
        BtnOnline->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(BtnOnline);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        BtnAllUsers = new QPushButton(centralWidget);
        BtnAllUsers->setObjectName("BtnAllUsers");
        sizePolicy2.setHeightForWidth(BtnAllUsers->sizePolicy().hasHeightForWidth());
        BtnAllUsers->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(BtnAllUsers);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        BtnUpgrade = new QPushButton(centralWidget);
        BtnUpgrade->setObjectName("BtnUpgrade");
        sizePolicy2.setHeightForWidth(BtnUpgrade->sizePolicy().hasHeightForWidth());
        BtnUpgrade->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(BtnUpgrade);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        BtnDuel = new QPushButton(centralWidget);
        BtnDuel->setObjectName("BtnDuel");
        sizePolicy2.setHeightForWidth(BtnDuel->sizePolicy().hasHeightForWidth());
        BtnDuel->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(BtnDuel);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        BtnRate = new QPushButton(centralWidget);
        BtnRate->setObjectName("BtnRate");
        sizePolicy.setHeightForWidth(BtnRate->sizePolicy().hasHeightForWidth());
        BtnRate->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(BtnRate);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        showInfo = new QLabel(centralWidget);
        showInfo->setObjectName("showInfo");
        showInfo->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(showInfo);

        listWidgetUsers = new QListWidget(centralWidget);
        listWidgetUsers->setObjectName("listWidgetUsers");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(listWidgetUsers->sizePolicy().hasHeightForWidth());
        listWidgetUsers->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(listWidgetUsers);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        labelServer = new QLabel(centralWidget);
        labelServer->setObjectName("labelServer");

        horizontalLayout_3->addWidget(labelServer);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName("comboBox");

        horizontalLayout_3->addWidget(comboBox);

        BtnConfirm = new QPushButton(centralWidget);
        BtnConfirm->setObjectName("BtnConfirm");

        horizontalLayout_3->addWidget(BtnConfirm);


        verticalLayout_2->addLayout(horizontalLayout_3);

        labelSPkm = new QLabel(centralWidget);
        labelSPkm->setObjectName("labelSPkm");

        verticalLayout_2->addWidget(labelSPkm);

        verticalLayout_2->setStretch(1, 8);
        verticalLayout_2->setStretch(3, 15);

        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 9);
        horizontalLayout_2->setStretch(2, 3);
        horizontalLayout_2->setStretch(3, 9);
        horizontalLayout_2->setStretch(4, 1);

        verticalLayout_5->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 702, 23));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelUser->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelWho->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        BtnBadge->setText(QCoreApplication::translate("MainWindow", "Badge", nullptr));
        labelNum->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelNumBadge->setText(QString());
        labelAdv->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelAdvBadge->setText(QString());
        labelInfo->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        BtnLoginOut->setText(QCoreApplication::translate("MainWindow", "Login Out", nullptr));
        BtnOnline->setText(QCoreApplication::translate("MainWindow", "Online Users", nullptr));
        BtnAllUsers->setText(QCoreApplication::translate("MainWindow", "All users", nullptr));
        BtnUpgrade->setText(QCoreApplication::translate("MainWindow", "Upgrade", nullptr));
        BtnDuel->setText(QCoreApplication::translate("MainWindow", "Duel Game", nullptr));
        BtnRate->setText(QCoreApplication::translate("MainWindow", "Winning Rate", nullptr));
        showInfo->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelServer->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        BtnConfirm->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        labelSPkm->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
