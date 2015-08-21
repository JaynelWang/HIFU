#include "docontroller.h"
#include "mainwindow.h"

DOController::DOController(QWidget *parent) : QObject(parent)
{
    m_DO = new StaticDO;
}

DOController::~DOController()
{
    m_DO->~StaticDO();
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
