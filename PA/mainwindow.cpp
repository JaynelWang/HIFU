#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_PAController = new PowerAmp();
    ui->textEdit->setText(m_PAController->m_serialPort->portName());
    connect(m_PAController->m_serialPort,SIGNAL(readyRead()),SLOT(handleReadyRead()));
    connect(this,SIGNAL(readDone(QByteArray)),this,SLOT(handleReadDone(QByteArray)));
    connect(ui->pushButton_send,SIGNAL(clicked()),SLOT(handleWrite()));
    connect(&m_timer,SIGNAL(timeout()),SLOT(handleTimeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_PAController;
}

void MainWindow::handleWrite()
{
    m_PAController->m_serialPort->write(QByteArray::fromHex(ui->lineEdit->text().toLatin1()));
}

void MainWindow::handleReadyRead()
{
    m_readData.append(m_serialPort->readAll());
    startTimer(m_timer);
}

void MainWindow::startTimer(QTimer &timer)
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

void MainWindow::handleTimeout()
{
    if (!m_serialPort->bytesAvailable())
    {
        QByteArray readData = m_readData;
        m_readData.clear();
        emit readDone(readData);
    }
}

void MainWindow::handleReadDone(QByteArray readData)
{  
    ui->textEdit->setText(readData.toHex());
}
