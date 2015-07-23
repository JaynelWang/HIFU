/********************************************************************************
** Form generated from reading UI file 'staticdo.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATICDO_H
#define UI_STATICDO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QPushButton *btnOK;
    QLineEdit *DutyCycleEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *SonicationTimeEdit;
    QLineEdit *SonicationPeriodEdit;
    QLineEdit *CoolingTimeEdit;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *btnCancel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(332, 260);
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(71, 90, 54, 16));
        btnOK = new QPushButton(Form);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(80, 190, 71, 23));
        DutyCycleEdit = new QLineEdit(Form);
        DutyCycleEdit->setObjectName(QStringLiteral("DutyCycleEdit"));
        DutyCycleEdit->setGeometry(QRect(131, 90, 111, 20));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(23, 10, 91, 20));
        label_3 = new QLabel(Form);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(13, 50, 101, 20));
        label_4 = new QLabel(Form);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 130, 91, 20));
        SonicationTimeEdit = new QLineEdit(Form);
        SonicationTimeEdit->setObjectName(QStringLiteral("SonicationTimeEdit"));
        SonicationTimeEdit->setGeometry(QRect(130, 10, 113, 20));
        SonicationPeriodEdit = new QLineEdit(Form);
        SonicationPeriodEdit->setObjectName(QStringLiteral("SonicationPeriodEdit"));
        SonicationPeriodEdit->setGeometry(QRect(130, 50, 113, 20));
        CoolingTimeEdit = new QLineEdit(Form);
        CoolingTimeEdit->setObjectName(QStringLiteral("CoolingTimeEdit"));
        CoolingTimeEdit->setGeometry(QRect(130, 130, 113, 20));
        label_5 = new QLabel(Form);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(260, 90, 54, 12));
        label_6 = new QLabel(Form);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(260, 10, 54, 12));
        label_7 = new QLabel(Form);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(260, 50, 54, 12));
        label_8 = new QLabel(Form);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(260, 130, 21, 20));
        btnCancel = new QPushButton(Form);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(190, 190, 75, 23));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label->setText(QApplication::translate("Form", "DutyCycle", 0));
        btnOK->setText(QApplication::translate("Form", "OK", 0));
        label_2->setText(QApplication::translate("Form", "SonicationTime", 0));
        label_3->setText(QApplication::translate("Form", "SonicationPeriod", 0));
        label_4->setText(QApplication::translate("Form", "CoolingTime", 0));
        label_5->setText(QApplication::translate("Form", "%", 0));
        label_6->setText(QApplication::translate("Form", "s", 0));
        label_7->setText(QApplication::translate("Form", "ms", 0));
        label_8->setText(QApplication::translate("Form", "s", 0));
        btnCancel->setText(QApplication::translate("Form", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATICDO_H
