#include "staticdo.h"
#include <QMessageBox>

StaticDO::StaticDO(QObject *parent)
    : QObject(parent)
{
    m_port = 0;
    m_state = (quint8)0;
    m_deviceName = DEVICENAME;

    selectDevice(DEVICENAME);
}

StaticDO::~StaticDO()
{
    m_instantDOCtrl->Dispose();
}

InstantDoCtrl * StaticDO::selectDevice(QString deviceName)
{
    std::wstring description = deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    m_instantDOCtrl = AdxInstantDoCtrlCreate();

    ErrorCode errorCode = Success;
    errorCode = m_instantDOCtrl->setSelectedDevice(selected);
    checkError(errorCode);

    return m_instantDOCtrl;
}

void StaticDO::setPort(int port)
{
    this->m_port = port;
}

int StaticDO::getPort()
{
    return this->m_port;
}

void StaticDO::setState(quint8 state)
{
    this->m_state = state;
}

quint8 StaticDO::getState()
{
    return this->m_state;
}

void StaticDO::writeData(int port, quint8 state)
{
    ErrorCode errorCode = Success;
    errorCode = m_instantDOCtrl->Write(port, state);
    checkError(errorCode);
}

void StaticDO::checkError(ErrorCode errorCode)
{
    if (errorCode != Success) {
        QString message = "Sorry, there are some errors occurred, Error Code: 0x" +
            QString::number(errorCode, 16).right(8);
        QMessageBox::information(NULL,"Warning Information", message,QMessageBox::Ok);
    }
}
