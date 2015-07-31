#include "poweramp.h"
#include <QObject>
#include <QBitArray>
#include <QThread>
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>

PowerAmp::PowerAmp(QObject *parent) : QObject(parent)
{
    QSerialPort* serialPort = identifyProbe();
    if (serialPort)
        m_serialPort = serialPort;
    if (!m_serialPort->isOpen())
        m_serialPort->open(QIODevice::ReadWrite);

    connect(m_serialPort,SIGNAL(error(QSerialPort::SerialPortError)),SLOT(handleError(QSerialPort::SerialPortError)));
    m_bytesRead = "";
}

PowerAmp::~PowerAmp()
{

}

int PowerAmp::validatePowerAmp(int ID)
{
    int DEV_COUNT_MAX = 127;
    int PowerAmpId;

    if (0 <= ID && ID <= DEV_COUNT_MAX)
        PowerAmpId = ID;
    else
        PowerAmpId = -1;

    return PowerAmpId;
}

double PowerAmp::validateVoltage(double Volt)
{
    double VOLT_MAX = 18;

    if (Volt < 0 || Volt > VOLT_MAX)
        Volt = -1;
    return Volt;
}

bool PowerAmp::validateEcho(QByteArray BytesEcho, QByteArray BytePowerAmpId)
{
    bool IsEchoBytesValid = false;
    bool ok;
    QByteArray BytesVolt, BytePowerAmpId_Original;

    BytesVolt.append(BytesEcho.mid(2,4));
    int sum = BytePowerAmpId.toInt(&ok,16) - 128;
    BytePowerAmpId_Original.setNum(sum,16);
    if (sum < 16)
        BytePowerAmpId_Original.prepend("0");

    bool IsPowerAmpIdValid = (BytesEcho.mid(0,2) == BytePowerAmpId_Original);
    if (IsPowerAmpIdValid)
    {
        bool IsRestBytesValid = (BytesEcho.mid(6,2) == getCheckByte(BytesEcho.mid(0,2), BytesVolt));
         if (IsRestBytesValid)
             IsEchoBytesValid = true;
    }

    return IsEchoBytesValid;
}

QByteArray PowerAmp::getPowerAmpIdByte(int ID)
{
    QByteArray BytePowerAmpId;

    if (validatePowerAmp(ID) >= 0)
        BytePowerAmpId = QByteArray::number(validatePowerAmp(ID) + 128, 16).toUpper();
    return BytePowerAmpId;
}

QByteArray PowerAmp::getVoltageBytes(PowerAmpAction Action, double Volt)
{
    QByteArray BytesVolt;
    switch (Action)
       {case RESET:
           BytesVolt.append("0000");
           break;
        case START:
            if (validateVoltage(Volt) >= 0)
            {
                Volt = ceil(validateVoltage(Volt) * 10);
                if (Volt >= 128)
                {
                    int sum = (int)Volt - 128;
                    BytesVolt.setNum(sum, 16);
                    if (sum < 16)
                        BytesVolt.prepend("0");
                    BytesVolt.prepend("41");
                }
                else
                {
                    BytesVolt.setNum((int)Volt, 16);
                    if ((int)Volt < 16)
                        BytesVolt.prepend("0");
                    BytesVolt.prepend("40");
                }
            }
            break;
        case ECHO:
            BytesVolt.append("2000");
            break;
    }
    return BytesVolt;
}

QByteArray PowerAmp::getCheckByte(QByteArray BytePowerAmpId, QByteArray BytesVolt)
{
    QByteArray ByteCheck;
    bool ok;

    if (!BytePowerAmpId.isEmpty() && !BytesVolt.isEmpty())
    {
        int sum = BytesVolt.mid(0,2).toInt(&ok,16) + BytesVolt.mid(2,2).toInt(&ok,16) + BytePowerAmpId.toInt(&ok,16);
        if (sum >255)
            sum -= 256;
        if (sum > 127)
            sum -= 128;
        ByteCheck.setNum(sum,16);
        if (sum < 16)
            ByteCheck.prepend("0");
    }
    return ByteCheck;
}

bool PowerAmp::resetSinglePowerAmp(int PowerAmpId)
{
    bool Success = false;
    PowerAmpAction PA_Action = RESET;

    QByteArray BytePowerAmpId = getPowerAmpIdByte(PowerAmpId);
    QByteArray BytesVolt = getVoltageBytes(PA_Action,(float)0);
    QByteArray ByteCheck = getCheckByte(BytePowerAmpId, BytesVolt);

    if (!ByteCheck.isEmpty())
    {
        QByteArray BytesSend;
        BytesSend.append(BytePowerAmpId);
        BytesSend.append(BytesVolt);
        BytesSend.append(ByteCheck);
        m_serialPort->write(QByteArray::fromHex(BytesSend));
        int n = 0;
        if (m_serialPort->waitForReadyRead(5))
        {
            n += 1;
        }
        qDebug("resetSingle time : %d ms" , n*5);
        //qint64 isBytesAvailable = m_serialPort->bytesAvailable();
        m_bytesRead = m_serialPort->readAll();
        if (!m_bytesRead.isEmpty())
        {
            if (checkReadBytes(m_bytesRead.toHex(), BytesSend))
                Success = true;
        }
    }

    m_bytesRead = "";
    return Success;
}

bool PowerAmp::resetAllPowerAmp()
{
    int ID_MIN = 1;
    int ID_MAX = 112;
    bool Success = false;
    m_errorPowerAmpIdForReset.clear();
    int PowerAmpId;
    int SafeCounter;

    for (PowerAmpId = ID_MIN; PowerAmpId <= ID_MAX; PowerAmpId++)
    {
        SafeCounter = 0;
        while (true)
        {
            QThread::msleep(100);
            if (resetSinglePowerAmp(PowerAmpId))
                break;
            else
                SafeCounter += 1;

            if (SafeCounter == 4)
            {
                m_errorPowerAmpIdForReset.append(PowerAmpId);
                break;
            }
        }
    }

    if (m_errorPowerAmpIdForReset.isEmpty())
        Success = true;

    return Success;
}

bool PowerAmp::startSinglePowerAmp(int PowerAmpId, double Volt)
{
    bool Success = false;
    PowerAmpAction PA_Action = START;

    QByteArray BytePowerAmpId = getPowerAmpIdByte(PowerAmpId);
    QByteArray BytesVolt = getVoltageBytes(PA_Action,Volt);
    QByteArray ByteCheck = getCheckByte(BytePowerAmpId, BytesVolt);

    if (!ByteCheck.isEmpty())
    {
        QByteArray BytesSend;
        BytesSend.append(BytePowerAmpId);
        BytesSend.append(BytesVolt);
        BytesSend.append(ByteCheck);

        m_serialPort->write(QByteArray::fromHex(BytesSend));
        int n = 0;
        if (m_serialPort->waitForReadyRead(5))
        {
            n += 1;
        }
        qDebug("startSingle time : %d ms" , n*5);
        //qint64 isBytesAvailable = m_serialPort->bytesAvailable();
        m_bytesRead = m_serialPort->readAll();
        if (!m_bytesRead.isEmpty())
        {
            if (checkReadBytes(m_bytesRead.toHex(), BytesSend))
            Success = true;
        }
    }

    m_bytesRead = "";
    return Success;
}

bool PowerAmp::startAllPowerAmp(double Volt)
{
    int ID_MIN = 1;
    int ID_MAX = 112;
    bool Success = false;
    m_errorPowerAmpIdForStart.clear();
    int PowerAmpId;
    int SafeCounter;

    for (PowerAmpId = ID_MIN; PowerAmpId <= ID_MAX; PowerAmpId++)
    {
        SafeCounter = 0;
        while (true)
        {
            QThread::msleep(100);
            if (startSinglePowerAmp(PowerAmpId, Volt))
                break;
            else
                SafeCounter += 1;

            if (SafeCounter == 4)
            {
                m_errorPowerAmpIdForStart.append(PowerAmpId);
                break;
            }
        }
    }

    if (m_errorPowerAmpIdForStart.isEmpty())
        Success = true;

    return Success;
}

double PowerAmp::echoPowerAmp(int PowerAmpId)
{
    double Volt = -1;
    PowerAmpAction PA_Action = ECHO;

    QByteArray BytePowerAmpId = getPowerAmpIdByte(PowerAmpId);
    QByteArray BytesVolt = getVoltageBytes(PA_Action,(float)0);
    QByteArray ByteCheck = getCheckByte(BytePowerAmpId, BytesVolt);

    if (!ByteCheck.isEmpty())
    {
        QByteArray BytesSend;
        BytesSend.append(BytePowerAmpId);
        BytesSend.append(BytesVolt);
        BytesSend.append(ByteCheck);

        m_serialPort->write(QByteArray::fromHex(BytesSend));
        int n = 0;
        if (m_serialPort->waitForReadyRead(5))
        {
            n += 1;
        }
        qDebug("echoPowerAmp time : %d ms" , n*5);
        m_bytesRead = m_serialPort->readAll();
        m_bytesRead = m_bytesRead.toHex();
        bool IsLengthValid = (m_bytesRead.size() / 2 == 4);
        if (IsLengthValid)
        {
            bool IsEchoBytesValid = validateEcho(m_bytesRead, BytePowerAmpId);
            if (IsEchoBytesValid)
                Volt = bytes2voltage(m_bytesRead);
        }
    }

    m_bytesRead = "";
    return Volt;
}

bool PowerAmp::checkReadBytes(QByteArray BytesRead, QByteArray BytesSend)
{
    bool Valid = false;
    bool ok;

    int LengthOfBytesRead = BytesRead.size() / 2;
    bool IsLengthValid = (LengthOfBytesRead == 4);
    if (IsLengthValid)
        {QByteArray BytePowerAmpId_Original;
        int sum = BytesSend.mid(0,2).toInt(&ok, 16) - 128;
         BytePowerAmpId_Original.setNum(sum, 16);
         if (sum < 16)
             BytePowerAmpId_Original.prepend("0");
         bool IsReadBytesValid = (BytesRead.mid(0,2) == BytePowerAmpId_Original &&
                                  BytesRead.mid(2,2) == BytesSend.mid(2,2) &&
                                  BytesRead.mid(4,2) == BytesSend.mid(4,2) &&
                                  BytesRead.mid(6,2) == BytesSend.mid(6,2));
        if (IsReadBytesValid)
            Valid = true;
        }

    return Valid;
}

double PowerAmp::bytes2voltage(QByteArray BytesEcho)
{
    double Volt = -1;
    QByteArray BytesEcho_2 = BytesEcho.mid(2,2);
    QByteArray BytesEcho_3 = BytesEcho.mid(4,2);
    bool ok;

    int bithigh = BytesEcho_2.toInt(&ok, 16) % 2;
    if (bithigh)
        Volt = (double)(BytesEcho_3.toInt(&ok, 16) + 128) / 10;
    else
        Volt = (double)BytesEcho_3.toInt(&ok, 16) / 10;
    Volt = validateVoltage(Volt);

    return Volt;
}

QSerialPort* PowerAmp::identifyProbe()
{
    QString bytesSend = "81000001";
    QString bytesEcho = "01000001";

    QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList)
    {
        QSerialPort *serialPort = new QSerialPort(serialPortInfo);
        serialPort->open(QIODevice::ReadWrite);
        serialPort->write(QByteArray::fromHex(bytesSend.toLatin1()));
        serialPort->waitForReadyRead(500);
        QByteArray readData = serialPort->readAll();
        if (readData == QByteArray::fromHex(bytesEcho.toLatin1()))
            return serialPort;
        else
            delete serialPort;
    }
    return NULL;
}

void PowerAmp::handleError(QSerialPort::SerialPortError error)
{
    emit errorOccur(m_serialPort->errorString());
}
