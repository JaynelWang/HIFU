#include "docontroller.h"
#include "mainwindow.h"

DOController::DOController(QWidget *parent) : QObject(parent)
{
    m_DO = new StaticDO;
    m_currentCycleNum = 0;
    m_currentSpotNum = 0;
    m_numOfTransducer = 112;
}

DOController::~DOController()
{
    m_DO->~StaticDO();
}

void DOController::setSpotNum(int spotNum)
{
    this->m_spotNum = spotNum;
}

int DOController::getSpotNum()
{
    return this->m_spotNum;
}

void DOController::sendPhase(int channel, quint8 phase)
{
    m_DO->setPort(portValue.portForChannel);
    m_DO->setState((quint8)channel);
    m_DO->writeData(m_DO->m_port,m_DO->m_state);

    m_DO->setPort(portValue.portForPhase);
    m_DO->setState(phase);
    m_DO->writeData(m_DO->m_port,m_DO->m_state);
}

void DOController::loadPhase()
{
    quint8 byteForLoad = (quint8)128;
    quint8 byteForLock = (quint8)0;

    m_DO->setPort(portValue.portForLoad);
    m_DO->setState(byteForLoad);
    m_DO->writeData(m_DO->m_port,m_DO->m_state);
    m_DO->setState(byteForLock);
    m_DO->writeData(m_DO->m_port,m_DO->m_state);
}

void DOController::enableDO()
{
    quint8 byteForEnable = (quint8)64;

    m_DO->setPort(portValue.portForEnable);
    m_DO->setState(byteForEnable);
    m_DO->writeData(m_DO->m_port,m_DO->m_state);
}

void DOController::disableDO()
{
    quint8 byteForDisable = (quint8)0;

    m_DO->setPort(portValue.portForDisable);
    m_DO->setState(byteForDisable);
    m_DO->writeData(m_DO->m_port,m_DO->m_state);
}

void DOController::startSending()
{
    real_T Voltage[112],AngleT[112];
    focusNum spotNum = 1;
    int i;
    PhaseInfo(spotNum,m_focus.focus_X[m_currentSpotNum],m_focus.focus_Y[m_currentSpotNum],m_focus.focus_Z[m_currentSpotNum],Voltage,AngleT);
    for (i = 0; i < m_numOfTransducer; i++)
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
    m_currentCycleNum = 0;
    m_currentSpotNum = 0;
    startSending();
}

void DOController::CtrlTimerFcn()
{
    m_CtrlTimer.stop();
    switch (m_timerFlag){
        case 0:
            qDebug("timeOn: %d",m_currentCycleNum+1);
            disableDO();
            m_timerFlag = 1;
            m_CtrlTimer.singleShot(m_dutyOffTime,this,SLOT(CtrlTimerFcn()));
            m_CtrlTimer.start();
            break;
        case 1:
            m_currentCycleNum += 1;
            qDebug("timeOff: %d",m_currentCycleNum);
            if (m_currentCycleNum < m_cycleNum)
            {
                enableDO();
                m_timerFlag = 0;
                m_CtrlTimer.singleShot(m_dutyOnTime,this,SLOT(CtrlTimerFcn()));
                m_CtrlTimer.start();
            }
            else if (m_currentCycleNum = m_cycleNum)
            {
                m_timerFlag = 2;
                m_CtrlTimer.singleShot(m_coolingTime*1000,this,SLOT(CtrlTimerFcn()));
                m_CtrlTimer.start();
            }
            break;
        case 2:
            m_currentSpotNum += 1;
            qDebug("timeCool: %d",m_currentSpotNum);
            m_currentCycleNum = 0;

            if (m_currentSpotNum < m_spotNum)
                startSending();
            else if (m_currentSpotNum = m_spotNum)
                {
                    m_DO->~StaticDO();
                    exit(0);
                }
            break;

        }
}

void DOController::setFocusCoordinate(spotCoordinate focus)
{
    m_focus = focus;
}
