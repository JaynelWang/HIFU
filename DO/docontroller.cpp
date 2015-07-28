#include "docontroller.h"
#include "mainwindow.h"

DOController::DOController(QWidget *parent) : QObject(parent)
{
    m_DO = new StaticDO;
    m_currentCycleCount = 0;
    m_currentSpotCount = 0;
    m_transducerCount = 112;
}

DOController::~DOController()
{
    m_DO->~StaticDO();
}

int DOController::getSpotCount()
{
    return this->m_spotCount;
}

void DOController::sendPhase(int channel, quint8 phase)
{
    int port2send = PORT_CHANNEL;
    quint8 data2send = (quint8)channel;
    m_DO->writeData(port2send, data2send);

    port2send = PORT_PHASE;
    m_DO->writeData(port2send, phase);
}

void DOController::loadPhase()
{
    int port2send = PORT_LOAD;
    quint8 byteForLoad = (quint8)128;
    quint8 byteForLock = (quint8)0;    
    m_DO->writeData(port2send,byteForLoad);
    m_DO->writeData(port2send,byteForLock);
}

void DOController::enableDO()
{
    int port2send = PORT_ENABLE;
    quint8 byteForEnable = (quint8)64;
    m_DO->writeData(port2send,byteForEnable);
}

void DOController::disableDO()
{
    int port2send = PORT_DISABLE;
    quint8 byteForDisable = (quint8)0;
    m_DO->writeData(port2send,byteForDisable);
}

void DOController::startSending()
{
    real_T Voltage[112],AngleT[112];
    spotForCount spotCount = 1;
    int i;
    PhaseInfo(spotCount,m_spot[m_currentSpotCount].spot_X,m_spot[m_currentSpotCount].spot_Y,m_spot[m_currentSpotCount].spot_Z,Voltage,AngleT);
    for (i = 0; i < m_transducerCount; i++)
    {
        sendPhase(i,(quint8)AngleT[i]);
        loadPhase();
    }
    enableDO();

    m_timerFlag = 0;
    m_CtrlTimer.singleShot(m_dutyOnTime,this,SLOT(CtrlTimerFcn()));
    m_CtrlTimer.start();
}

void DOController::restart()
{
    if (m_CtrlTimer.isActive())
        m_CtrlTimer.stop();
    m_currentCycleCount = 0;
    m_currentSpotCount = 0;
    startSending();
}

void DOController::CtrlTimerFcn()
{
    m_CtrlTimer.stop();
    switch (m_timerFlag){
        case 0:
            qDebug("timeOn: %d",m_currentCycleCount + 1);
            disableDO();
            m_timerFlag = 1;
            m_CtrlTimer.singleShot(m_dutyOffTime,this,SLOT(CtrlTimerFcn()));
            m_CtrlTimer.start();
            break;
        case 1:
            m_currentCycleCount += 1;
            qDebug("timeOff: %d",m_currentCycleCount);
            if (m_currentCycleCount < m_cycleCount)
            {
                enableDO();
                m_timerFlag = 0;
                m_CtrlTimer.singleShot(m_dutyOnTime,this,SLOT(CtrlTimerFcn()));
                m_CtrlTimer.start();
            }
            else if (m_currentCycleCount = m_cycleCount)
            {
                m_timerFlag = 2;
                m_CtrlTimer.singleShot(m_sonicationParameter.coolingTime*1000,this,SLOT(CtrlTimerFcn()));
                m_CtrlTimer.start();
            }
            break;
        case 2:
            m_currentSpotCount += 1;
            qDebug("timeCool: %d",m_currentSpotCount);
            m_currentCycleCount = 0;

            if (m_currentSpotCount < m_spotCount)
                startSending();
            else if (m_currentSpotCount = m_spotCount)
                {
                    m_DO->~StaticDO();
                    exit(0);
                }
            break;

        }
}

void DOController::setSpot(QList<SpotCoordinate> spot)
{
    m_spot = spot;
    m_spotCount = m_spot.size();
}
