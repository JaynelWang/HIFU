#include "staticdo.h"
#include <QMessageBox>

StaticDO::StaticDO(QObject *parent)
    : QObject(parent)
{
    m_deviceName = DEVICE_ID;
    selectDevice(DEVICE_ID);
}

StaticDO::~StaticDO()
{
    m_instantDOCtrl->Dispose();
}

void StaticDO::selectDevice(QString deviceName)
{
    std::wstring description = deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    m_instantDOCtrl = AdxInstantDoCtrlCreate();

    ErrorCode errorCode = Success;
    errorCode = m_instantDOCtrl->setSelectedDevice(selected);
    checkError(errorCode);
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
        QString error = "ox" + QString::number(errorCode, 16).right(8);
        emit errorOccurred(error);
    }
}
