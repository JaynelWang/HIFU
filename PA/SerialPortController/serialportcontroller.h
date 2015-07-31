#ifndef SERIALPORTCONTROLLER
#define SERIALPORTCONTROLLER

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

class SerialPortController : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortController(QSerialPort *serialPort, QObject *parent = 0);
    ~SerialPortController();
    QSerialPort *m_serialPort;

    void write(const QByteArray &writeData);

signals:
    void readDone(QByteArray readData);
    void errorOccur(QString errorString);

public slots:

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QByteArray m_readData;
    QTimer m_timer;

    void startTimer(QTimer &timer);
};

#endif // SERIALPORTCONTROLLER

