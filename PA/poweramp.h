#ifndef POWERAMP
#define POWERAMP

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QtSerialPort/QSerialPort>

class PowerAmp : public QObject
{
    Q_OBJECT

public:
    PowerAmp(QObject *parent = 0);
    ~PowerAmp();
    bool resetSinglePowerAmp(int PowerAmpId);
    bool resetAllPowerAmp();
    bool startSinglePowerAmp(int PowerAmpId, double Volt);
    bool startAllPowerAmp(double Volt);
    double echoPowerAmp(int PowerAmpId);

signals:
    void errorOccur(QString errorString);

private:
    enum PowerAmpAction{RESET,START,ECHO};    
    QSerialPort* m_serialPort;
    QByteArray m_bytesRead;    
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
    void handleError(QSerialPort::SerialPortError error);
};

#endif // POWERAMP

