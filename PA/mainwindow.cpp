#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_PAController = new PowerAmp();
    if (m_PAController->m_serialPortController)
        ui->textEdit->setText("Open Successfully.");
    connect(m_PAController->m_serialPortController,SIGNAL(readDone(QByteArray)),SLOT(handleRead(QByteArray)));
    connect(m_PAController->m_serialPortController,SIGNAL(errorOccur(QString)),SLOT(handleError(QString)));
    connect(ui->pushButton_send,SIGNAL(clicked()),SLOT(handleWrite()));
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
