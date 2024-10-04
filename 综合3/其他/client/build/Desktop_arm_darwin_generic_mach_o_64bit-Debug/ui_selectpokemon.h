/********************************************************************************
** Form generated from reading UI file 'selectpokemon.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPOKEMON_H
#define UI_SELECTPOKEMON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SelectPkm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelInfo;
    QComboBox *comboBoxPkm;
    QPushButton *BtnCfm;
    QLabel *labelPkmInfo;

    void setupUi(QDialog *SelectPkm)
    {
        if (SelectPkm->objectName().isEmpty())
            SelectPkm->setObjectName("SelectPkm");
        SelectPkm->resize(423, 333);
        verticalLayout_2 = new QVBoxLayout(SelectPkm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelInfo = new QLabel(SelectPkm);
        labelInfo->setObjectName("labelInfo");

        horizontalLayout->addWidget(labelInfo);

        comboBoxPkm = new QComboBox(SelectPkm);
        comboBoxPkm->setObjectName("comboBoxPkm");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxPkm->sizePolicy().hasHeightForWidth());
        comboBoxPkm->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBoxPkm);

        BtnCfm = new QPushButton(SelectPkm);
        BtnCfm->setObjectName("BtnCfm");
        sizePolicy.setHeightForWidth(BtnCfm->sizePolicy().hasHeightForWidth());
        BtnCfm->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(BtnCfm);


        verticalLayout->addLayout(horizontalLayout);

        labelPkmInfo = new QLabel(SelectPkm);
        labelPkmInfo->setObjectName("labelPkmInfo");

        verticalLayout->addWidget(labelPkmInfo);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 6);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SelectPkm);

        QMetaObject::connectSlotsByName(SelectPkm);
    } // setupUi

    void retranslateUi(QDialog *SelectPkm)
    {
        SelectPkm->setWindowTitle(QCoreApplication::translate("SelectPkm", "Dialog", nullptr));
        labelInfo->setText(QCoreApplication::translate("SelectPkm", "Select a Pokemon to Send", nullptr));
        BtnCfm->setText(QCoreApplication::translate("SelectPkm", "Confirm", nullptr));
        labelPkmInfo->setText(QCoreApplication::translate("SelectPkm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPkm: public Ui_SelectPkm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPOKEMON_H
