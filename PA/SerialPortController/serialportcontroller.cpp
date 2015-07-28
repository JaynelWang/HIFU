#include "serialportcontroller.h"

SerialPortController::SerialPortController(QSerialPort *serialPort, QObject *parent) : QObject(parent),
    m_serialPort(serialPort)
{
    m_timer.setSingleShot(true);
    connect(m_serialPort,SIGNAL(readyRead()),SLOT(handleReadyRead()));
    connect(m_serialPort,SIGNAL(error(QSerialPort::SerialPortError)),SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&m_timer,SIGNAL(timeout()),SLOT(handleTimeout()));

    if (!m_serialPort->isOpen())
    {
        m_serialPort->open(QIODevice::ReadWrite);
    }
}

SerialPortController::~SerialPortController()
{
}

void SerialPortController::write(const QByteArray &writeData)
{
    m_serialPort->write(writeData);
}

void SerialPortController::handleReadyRead()
{
    m_readData.append(m_serialPort->readAll());
    startTimer(m_timer);
}

void SerialPortController::handleTimeout()
{
    if (!m_serialPort->bytesAvailable())
    {
        QByteArray readData = m_readData;
        m_readData.clear();
        emit readDone(readData);
    }
}

void SerialPortController::handleError(QSerialPort::SerialPortError error)
{
    emit errorOccur(m_serialPort->errorString());
}

void SerialPortController::startTimer(QTimer &timer)
{
    if (!timer.isActive())
    {
        int period = 500;
        timer.start(period);
    }else
    {
        timer.stop();
        int period = 500;
        timer.start(period);
    }
}
