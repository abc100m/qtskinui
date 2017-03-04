/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>
#include "state_button.h"

QT_BEGIN_NAMESPACE

class Ui_UI_Main_Form
{
public:
    Common_Button *btnImport;
    QRadioButton *btnLeftToRight;
    QRadioButton *btnRightToLeft;
    Common_Button *btnAbout;
    QRadioButton *btnStretch;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *UI_Main_Form)
    {
        if (UI_Main_Form->objectName().isEmpty())
            UI_Main_Form->setObjectName(QStringLiteral("UI_Main_Form"));
        btnImport = new Common_Button(UI_Main_Form);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        btnImport->setGeometry(QRect(40, 90, 241, 41));
        btnImport->setFlat(false);
        btnLeftToRight = new QRadioButton(UI_Main_Form);
        buttonGroup = new QButtonGroup(UI_Main_Form);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(btnLeftToRight);
        btnLeftToRight->setObjectName(QStringLiteral("btnLeftToRight"));
        btnLeftToRight->setGeometry(QRect(40, 150, 111, 16));
        btnLeftToRight->setCheckable(true);
        btnLeftToRight->setChecked(true);
        btnRightToLeft = new QRadioButton(UI_Main_Form);
        buttonGroup->addButton(btnRightToLeft);
        btnRightToLeft->setObjectName(QStringLiteral("btnRightToLeft"));
        btnRightToLeft->setGeometry(QRect(150, 150, 111, 16));
        btnAbout = new Common_Button(UI_Main_Form);
        btnAbout->setObjectName(QStringLiteral("btnAbout"));
        btnAbout->setGeometry(QRect(40, 210, 101, 31));
        btnStretch = new QRadioButton(UI_Main_Form);
        buttonGroup->addButton(btnStretch);
        btnStretch->setObjectName(QStringLiteral("btnStretch"));
        btnStretch->setGeometry(QRect(270, 150, 111, 16));

        retranslateUi(UI_Main_Form);

        QMetaObject::connectSlotsByName(UI_Main_Form);
    } // setupUi

    void retranslateUi(QWidget *UI_Main_Form)
    {
        UI_Main_Form->setWindowTitle(QApplication::translate("UI_Main_Form", "Form", 0));
        btnImport->setText(QApplication::translate("UI_Main_Form", "open background image(&O)", 0));
        btnLeftToRight->setText(QApplication::translate("UI_Main_Form", "left to right", 0));
        btnRightToLeft->setText(QApplication::translate("UI_Main_Form", "right to left", 0));
        btnAbout->setText(QApplication::translate("UI_Main_Form", "about(&H)...", 0));
        btnStretch->setText(QApplication::translate("UI_Main_Form", "stretch draw", 0));
    } // retranslateUi

};

namespace Ui {
    class UI_Main_Form: public Ui_UI_Main_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
