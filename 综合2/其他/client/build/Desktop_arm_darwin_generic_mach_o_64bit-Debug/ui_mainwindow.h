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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *labelInfo;
    QLabel *labelWho;
    QVBoxLayout *verticalLayout;
    QPushButton *BtnLoginOut;
    QSpacerItem *verticalSpacer;
    QPushButton *BtnOnline;
    QSpacerItem *verticalSpacer_2;
    QPushButton *BtnAllUsers;
    QVBoxLayout *verticalLayout_2;
    QLabel *showInfo;
    QListWidget *listWidgetUsers;
    QMenuBar *menuBar;
    QMenu *menuclient;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(753, 461);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setEnabled(true);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        radioButton_1 = new QRadioButton(centralWidget);
        radioButton_1->setObjectName("radioButton_1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButton_1->sizePolicy().hasHeightForWidth());
        radioButton_1->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(radioButton_1);

        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName("radioButton_2");
        sizePolicy.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(centralWidget);
        radioButton_3->setObjectName("radioButton_3");
        sizePolicy.setHeightForWidth(radioButton_3->sizePolicy().hasHeightForWidth());
        radioButton_3->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(radioButton_3);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);

        labelInfo = new QLabel(centralWidget);
        labelInfo->setObjectName("labelInfo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelInfo->sizePolicy().hasHeightForWidth());
        labelInfo->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelInfo, 2, 0, 1, 2);

        labelWho = new QLabel(centralWidget);
        labelWho->setObjectName("labelWho");
        labelWho->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelWho, 0, 0, 1, 2);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 4);

        horizontalLayout_2->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
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
        sizePolicy2.setHeightForWidth(BtnOnline->sizePolicy().hasHeightForWidth());
        BtnOnline->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(BtnOnline);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        BtnAllUsers = new QPushButton(centralWidget);
        BtnAllUsers->setObjectName("BtnAllUsers");
        sizePolicy2.setHeightForWidth(BtnAllUsers->sizePolicy().hasHeightForWidth());
        BtnAllUsers->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(BtnAllUsers);


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

        verticalLayout_2->addWidget(listWidgetUsers);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 5);

        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 753, 24));
        menuclient = new QMenu(menuBar);
        menuclient->setObjectName("menuclient");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuclient->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        radioButton_1->setText(QCoreApplication::translate("MainWindow", "Pokemon_1", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Pokemon_2", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Pokemon_3", nullptr));
        labelInfo->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelWho->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        BtnLoginOut->setText(QCoreApplication::translate("MainWindow", "Login Out", nullptr));
        BtnOnline->setText(QCoreApplication::translate("MainWindow", "Online Users", nullptr));
        BtnAllUsers->setText(QCoreApplication::translate("MainWindow", "All users", nullptr));
        showInfo->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menuclient->setTitle(QCoreApplication::translate("MainWindow", "client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
