#ifndef DOCONTROLLER
#define DOCONTROLLER

#include "staticdo.h"
#include <QObject>
#include <QTimer>

class DOController : public QObject
{
    Q_OBJECT
public:
    DOController(QWidget *parent = 0);
    ~DOController();
    int m_sonicationTime;
    int m_sonicationPeriod;
    int m_dutyCycle;
    int m_coolingTime;
    int m_dutyOnTime;
    int m_dutyOffTime;
    int m_cycleNum;
    void setFocusCoordinate(spotCoordinate focus);
    void setSpotNum(int spotNum);
    int getSpotNum();
    void startSending();
    void restart();

private:
    StaticDO *m_DO;
    int m_spotNum;
    int m_currentCycleNum;
    int m_currentSpotNum;
    int m_numOfTransducer;
    int m_timerFlag;
    QTimer m_CtrlTimer;
    spotCoordinate m_focus;
    void sendPhase(int channel, quint8 phase);
    void loadPhase();
    void enableDO();
    void disableDO();

private slots:
    void CtrlTimerFcn();
};







#endif // DOCONTROLLER

