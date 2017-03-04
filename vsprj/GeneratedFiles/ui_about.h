/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "state_button.h"

QT_BEGIN_NAMESPACE

class Ui_UI_About
{
public:
    QLabel *label;
    Common_Button *btnClose;
    QLabel *label_2;

    void setupUi(QWidget *UI_About)
    {
        if (UI_About->objectName().isEmpty())
            UI_About->setObjectName(QStringLiteral("UI_About"));
        UI_About->resize(324, 263);
        label = new QLabel(UI_About);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 50, 231, 61));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        btnClose = new Common_Button(UI_About);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(110, 150, 91, 31));
        label_2 = new QLabel(UI_About);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 100, 91, 21));

        retranslateUi(UI_About);

        btnClose->setDefault(true);


        QMetaObject::connectSlotsByName(UI_About);
    } // setupUi

    void retranslateUi(QWidget *UI_About)
    {
        UI_About->setWindowTitle(QApplication::translate("UI_About", "About", 0));
        label->setText(QApplication::translate("UI_About", "write solid code", 0));
        btnClose->setText(QApplication::translate("UI_About", "Close(&C)", 0));
        label_2->setText(QApplication::translate("UI_About", "dragon jiang", 0));
    } // retranslateUi

};

namespace Ui {
    class UI_About: public Ui_UI_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
