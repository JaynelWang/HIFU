#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "docontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    DOController *m_DOController;

private:
    QLabel *sonicationTime_label;
    QLabel *sonicationPeriod_label;
    QLabel *dutyCycle_label;
    QLabel *coolingTime_label;
    QLineEdit *sonicationTime_edit;
    QLineEdit *sonicationPeriod_edit;
    QLineEdit *dutyCycle_edit;
    QLineEdit *coolingTime_edit;
    QLabel *sonicationTimeUnit_label;
    QLabel *sonicationPeriodUnit_label;
    QLabel *dutyCycleUnit_label;
    QLabel *coolingTimeUnit_label;
    QPushButton *ok_btn;
    QPushButton *restart_btn;
    QPushButton *cancel_btn;
    QHBoxLayout *sonicationTime_layout;
    QHBoxLayout *sonicationPeriod_layout;
    QHBoxLayout *dutyCycle_layout;
    QHBoxLayout *coolingTime_layout;
    QHBoxLayout *button_layout;
    QVBoxLayout *mainLayout;    

private slots:
    void buttonCancelClicked();
    void buttonOKClicked();
    void buttonRestartClicked();
};

#endif // MAINWINDOW_H
