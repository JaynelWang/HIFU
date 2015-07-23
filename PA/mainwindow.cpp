#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSerialPort* serialPort = identifyProbe();
    if (serialPort)
    {
        m_PAController = new PowerAmp(serialPort);
        connect(m_PAController->m_serialPortController,SIGNAL(m_PAController->m_serialPortController->readDone(QByteArray)),SLOT(handleRead(QByteArray)));
        connect(m_PAController->m_serialPortController,SIGNAL(m_PAController->m_serialPortController->errorOccur(QString)),SLOT(handleError(QString)));
        connect(ui->pushButton_send,SIGNAL(clicked()),SLOT(handleWrite()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleWrite()
{
    m_PAController->m_serialPortController->write(QByteArray::fromHex(ui->lineEdit->text().toLatin1()));
}

void MainWindow::handleRead(QByteArray readData)
{
    ui->textEdit->setText(readData.toHex());
}

void MainWindow::handleError(QString errorString)
{
    ui->label_error->setText(errorString);
}

QSerialPort* MainWindow::identifyProbe()
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
        serialPort->waitForReadyRead(500);        
        QByteArray readData = serialPort->readAll();
        if (readData == QByteArray::fromHex(bytesEcho.toLatin1()))
        {
            ui->textEdit->setText(serialPort->portName());
            return serialPort;
        }else
        {
            delete serialPort;

        }
    }
    return NULL;
}
