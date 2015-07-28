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
    SonicationParameter m_sonicationParameter;
    int m_dutyOnTime;
    int m_dutyOffTime;
    int m_cycleCount;
    void setSpot(QList<SpotCoordinate> spot);
    int getSpotCount();
    void startSending();
    void restart();

private:
    StaticDO *m_DO;
    int m_spotCount;
    int m_currentCycleCount;
    int m_currentSpotCount;
    int m_transducerCount;
    int m_timerFlag;
    QTimer m_CtrlTimer;
    QList<SpotCoordinate> m_spot;
    void sendPhase(int channel, quint8 phase);
    void loadPhase();
    void enableDO();
    void disableDO();

private slots:
    void CtrlTimerFcn();
};







#endif // DOCONTROLLER

