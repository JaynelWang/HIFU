#ifndef POWERAMP
#define POWERAMP

#include <QObject>
#include <QByteArray>
#include <QList>
#include <serialportcontroller.h>

enum PowerAmpAction{RESET,START,ECHO};

class PowerAmp : public QObject
{
public:
    PowerAmp(QSerialPort *serialPort, QObject *parent = 0);
    ~PowerAmp();   
    SerialPortController *m_serialPortController;

private:
    QByteArray m_bytesRead;
    int m_readDoneFlag;    
    QList<int> m_errorPowerAmpIdForReset;
    QList<int> m_errorPowerAmpIdForStart;
    int validatePowerAmp(int ID);
    float validateVoltage(float Volt);
    bool validateEcho(QByteArray BytesEcho, QByteArray BytePowerAmpId);
    QByteArray getPowerAmpIdByte(int ID);
    QByteArray getVoltageBytes(PowerAmpAction Action, float Volt);
    QByteArray getCheckByte(QByteArray BytePowerAmpId, QByteArray BytesVolt );
    bool resetSinglePowerAmp(int PowerAmpId);
    bool resetAllPowerAmp();
    bool startSinglePowerAmp(int PowerAmpId, float Volt);
    bool startAllPowerAmp(float Volt);
    float echoPowerAmp(int PowerAmpId);
    bool checkReadBytes(QByteArray BytesRead, QByteArray BytesSend);
    float bytes2voltage(QByteArray BytesEcho);

private slots:
    void handleReadDone(QByteArray ReadData);
};

#endif // POWERAMP

