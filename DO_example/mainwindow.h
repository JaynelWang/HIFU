#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "docontroller.h"
#include "PhaseInfo/PhaseInfo.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

typedef real_T coordinate;
typedef uint8_T spotForCount;

struct SpotCoordinate
{
    coordinate spot_X;
    coordinate spot_Y;
    coordinate spot_Z;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setSpot(QList<SpotCoordinate> spot);
    int getSpotCount();

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
    QPushButton *pause_btn;
    QPushButton *restart_btn;
    QPushButton *cancel_btn;
    QHBoxLayout *sonicationTime_layout;
    QHBoxLayout *sonicationPeriod_layout;
    QHBoxLayout *dutyCycle_layout;
    QHBoxLayout *coolingTime_layout;
    QHBoxLayout *button_layout;
    QVBoxLayout *mainLayout;

    DOController *m_DOController;
    SonicationParameter m_sonicationParameter;
    int m_dutyOnTime;
    int m_dutyOffTime;
    int m_cycleCount;
    int m_spotCount;
    int m_currentCycleCount;
    int m_currentSpotCount;
    int m_transducerCount;
    int m_timerFlag;
    QTimer m_CtrlTimer;
    QList<SpotCoordinate> m_spot;
    void startSending();

private slots:
    void buttonCancelClicked();
    void buttonOKClicked();
    void buttonPauseClicked();
    void buttonRestartClicked();
    void CtrlTimerFcn();
};

#endif // MAINWINDOW_H
