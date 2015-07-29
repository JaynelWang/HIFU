#ifndef POWERAMP
#define POWERAMP

#include <QObject>
#include <QByteArray>
#include <QList>
#include "serialportcontroller.h"

class PowerAmp : public QObject
{
    Q_OBJECT
public:
    PowerAmp(QObject *parent = 0);
    ~PowerAmp();
    SerialPortController *m_serialPortController;
    bool resetSinglePowerAmp(int PowerAmpId);
    bool resetAllPowerAmp();
    bool startSinglePowerAmp(int PowerAmpId, double Volt);
    bool startAllPowerAmp(double Volt);
    double echoPowerAmp(int PowerAmpId);
    bool resetSinglePowerAmp(int PowerAmpId);
    bool resetAllPowerAmp();
    bool startSinglePowerAmp(int PowerAmpId, double Volt);
    bool startAllPowerAmp(double Volt);
    double echoPowerAmp(int PowerAmpId);

private:
    enum PowerAmpAction{RESET,START,ECHO};
    QByteArray m_bytesRead;
    int m_readDoneFlag;
    QList<int> m_errorPowerAmpIdForReset;
    QList<int> m_errorPowerAmpIdForStart;
    QSerialPort* identifyProbe();
    int validatePowerAmp(int ID);
    double validateVoltage(double Volt);
    bool validateEcho(QByteArray BytesEcho, QByteArray BytePowerAmpId);
    QByteArray getPowerAmpIdByte(int ID);
    QByteArray getVoltageBytes(PowerAmpAction Action, double Volt);
    QByteArray getCheckByte(QByteArray BytePowerAmpId, QByteArray BytesVolt );    
    bool checkReadBytes(QByteArray BytesRead, QByteArray BytesSend);
    double bytes2voltage(QByteArray BytesEcho);

private slots:
    void handleReadDone(QByteArray ReadData);
};

#endif // POWERAMP
