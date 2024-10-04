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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelPokemon;
    QTableWidget *tableWidgetPokemon;
    QLabel *labelUsers;
    QTableWidget *tableWidgetUsers;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        labelPokemon = new QLabel(centralwidget);
        labelPokemon->setObjectName("labelPokemon");

        verticalLayout->addWidget(labelPokemon);

        tableWidgetPokemon = new QTableWidget(centralwidget);
        tableWidgetPokemon->setObjectName("tableWidgetPokemon");

        verticalLayout->addWidget(tableWidgetPokemon);

        labelUsers = new QLabel(centralwidget);
        labelUsers->setObjectName("labelUsers");

        verticalLayout->addWidget(labelUsers);

        tableWidgetUsers = new QTableWidget(centralwidget);
        tableWidgetUsers->setObjectName("tableWidgetUsers");

        verticalLayout->addWidget(tableWidgetUsers);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
