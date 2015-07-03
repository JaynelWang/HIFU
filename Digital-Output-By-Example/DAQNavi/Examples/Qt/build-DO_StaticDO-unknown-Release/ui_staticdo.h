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
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StaticDOClass
{
public:
    QFrame *background;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *btnConfig;
    QLabel *label;

    void setupUi(QDialog *StaticDOClass)
    {
        if (StaticDOClass->objectName().isEmpty())
            StaticDOClass->setObjectName(QStringLiteral("StaticDOClass"));
        StaticDOClass->resize(470, 432);
        StaticDOClass->setMinimumSize(QSize(470, 432));
        StaticDOClass->setMaximumSize(QSize(470, 432));
        background = new QFrame(StaticDOClass);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(283, -6, 191, 91));
        background->setMinimumSize(QSize(191, 91));
        background->setAutoFillBackground(false);
        background->setStyleSheet(QStringLiteral("QFrame#background{background-image:url(:/StaticDO/Resources/Background.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        scrollArea = new QScrollArea(StaticDOClass);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(27, 69, 369, 317));
        scrollArea->setMinimumSize(QSize(369, 317));
        scrollArea->setMaximumSize(QSize(369, 317));
        scrollArea->setSizeIncrement(QSize(369, 317));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 341, 0));
        scrollAreaWidgetContents->setMinimumSize(QSize(341, 0));
        scrollArea->setWidget(scrollAreaWidgetContents);
        btnConfig = new QPushButton(StaticDOClass);
        btnConfig->setObjectName(QStringLiteral("btnConfig"));
        btnConfig->setGeometry(QRect(320, 396, 75, 23));
        btnConfig->setMinimumSize(QSize(75, 23));
        label = new QLabel(StaticDOClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 50, 361, 16));
        label->setMinimumSize(QSize(361, 16));
        label->setMaximumSize(QSize(361, 16));

        retranslateUi(StaticDOClass);

        QMetaObject::connectSlotsByName(StaticDOClass);
    } // setupUi

    void retranslateUi(QDialog *StaticDOClass)
    {
        StaticDOClass->setWindowTitle(QApplication::translate("StaticDOClass", "Static DO", 0));
        btnConfig->setText(QApplication::translate("StaticDOClass", "Configure...", 0));
        label->setText(QApplication::translate("StaticDOClass", "Port No.    Bit7                          4            3                             0         Hex", 0));
    } // retranslateUi

};

namespace Ui {
    class StaticDOClass: public Ui_StaticDOClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATICDO_H
