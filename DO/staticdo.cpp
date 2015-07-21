#include "staticdo.h"
#include <QMessageBox>
#include <QtGui>

StaticDO::StaticDO(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));

    NumOfTransducer = 112;
    Key = 0;
    State = (quint8)0;
    CurrentCycleNum = 0;
    CurrentSpotNum = 0;

    QIntValidator *ValidatorForSonicationTime = new QIntValidator(6,20,this);
    ui.SonicationTimeEdit->setValidator(ValidatorForSonicationTime);
    QIntValidator *ValidatorForSonicationPeriod = new QIntValidator(1,1000,this);
    ui.SonicationPeriodEdit->setValidator(ValidatorForSonicationPeriod);
    QIntValidator *ValidatorForDutyCycle = new QIntValidator(1,100,this);
    ui.DutyCycleEdit->setValidator(ValidatorForDutyCycle);
    QIntValidator *ValidatorForCoolingTime = new QIntValidator(1,500,this);
    ui.CoolingTimeEdit->setValidator(ValidatorForCoolingTime);

    selectDevice();
}

StaticDO::~StaticDO()
{
    if (CtrlTimer.isActive())
        CtrlTimer.stop();
    instantDOCtrl->Dispose();
}

void StaticDO::selectDevice()
{
    DeviceName = "USB-4751,BID#0";
    std::wstring description = DeviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    instantDOCtrl = AdxInstantDoCtrlCreate();

    ErrorCode errorCode = Success;
    errorCode = instantDOCtrl->setSelectedDevice(selected);
    checkError(errorCode);
}

void StaticDO::startSending()
{
    TimerFlag = 0;
    CtrlTimer.singleShot(DutyOnTime,this,SLOT(CtrlTimerFcn()));
    CtrlTimer.start();
}

void StaticDO::setSpotNum(int SpotNum)
{
    this->SpotNum = SpotNum;
}

int StaticDO::getSpotNum()
{
    return this->SpotNum;
}

void StaticDO::setKey(int Key)
{
    this->Key = Key;
}

int StaticDO::getKey()
{
    return this->Key;
}

void StaticDO::setState(quint8 State)
{
    this->State = State;
}

quint8 StaticDO::getState()
{
    return this->State;
}

void StaticDO::writeData(int Key, quint8 State)
{
    ErrorCode errorCode = Success;
    errorCode = instantDOCtrl->Write(Key, State);
    checkError(errorCode);
}

void StaticDO::sendPhase(int Channel, quint8 Phase)
{
    int PortForChannel = 4;
    int PortForPhase = 5;

    setKey(PortForChannel);
    setState((quint8)Channel);
    writeData(Key, State);

    setKey(PortForPhase);
    setState(Phase);
    writeData(Key, State);
}

void StaticDO::loadPhase()
{
    int PortForLoad = 3;
    quint8 ByteForLoad = (quint8)128;
    quint8 ByteForLock = (quint8)0;

    setKey(PortForLoad);
    setState(ByteForLoad);
    writeData(Key, State);
    setState(ByteForLock);
    writeData(Key, State);
}

void StaticDO::enableDO()
{
    int PortForEnable = 3;
    quint8 ByteForEnable = (quint8)64;

    setKey(PortForEnable);
    setState(ByteForEnable);
    writeData(Key, State);
}

void StaticDO::disableDO()
{
    int PortForDisable = 3;
    quint8 ByteForDisable = (quint8)0;

    setKey(PortForDisable);
    setState(ByteForDisable);
    writeData(Key, State);
}

void StaticDO::CtrlTimerFcn()
{   CtrlTimer.stop();
    switch (TimerFlag){
            case 0:
                qDebug("timeOn: %d",CurrentCycleNum+1);
                disableDO();
                TimerFlag = 1;
                CtrlTimer.singleShot(DutyOffTime,this,SLOT(CtrlTimerFcn()));
                CtrlTimer.start();
                break;
            case 1:
                CurrentCycleNum += 1;
                qDebug("timeOff: %d",CurrentCycleNum);
                if (CurrentCycleNum < CycleNum)
                {
                    enableDO();
                    TimerFlag = 0;
                    CtrlTimer.singleShot(DutyOnTime,this,SLOT(CtrlTimerFcn()));
                    CtrlTimer.start();
                }
                else if (CurrentCycleNum = CycleNum)
                {
                    TimerFlag = 2;
                    CtrlTimer.singleShot(CoolingTime*1000,this,SLOT(CtrlTimerFcn()));
                    CtrlTimer.start();
                }
                break;
            case 2:
                CurrentSpotNum += 1;
                qDebug("timeCool: %d",CurrentSpotNum);
                CurrentCycleNum = 0;

                if (CurrentSpotNum < SpotNum)
                {
                    real_T Voltage[112],AngleT[112];
                    int i;
                    PhaseInfo(1,Focus_X[CurrentSpotNum],Focus_Y[CurrentSpotNum],Focus_Z[CurrentSpotNum],Voltage,AngleT);
                    for (i = 0; i < NumOfTransducer; i++)
                    {
                        sendPhase(i,(quint8)AngleT[i]);
                        loadPhase();
                    }
                    enableDO();
                    startSending();

                    //enableDO();
                    //TimerFlag = 0;
                    //CtrlTimer.singleShot(DutyOnTime,this,SLOT(CtrlTimerFcn()));
                    //CtrlTimer.start();
                }
                else if (CurrentSpotNum = SpotNum)
                {
                    instantDOCtrl->Dispose();
                    exit(0);
                }
                break;

    }

}

void StaticDO::ButtonOKClicked()
{
    SonicationTime = ui.SonicationTimeEdit->text().toInt();
    SonicationPeriod = ui.SonicationPeriodEdit->text().toInt();
    DutyCycle = ui.DutyCycleEdit->text().toInt();
    CoolingTime = ui.CoolingTimeEdit->text().toInt();
    DutyOnTime = qFloor(SonicationPeriod * DutyCycle / 100);
    DutyOffTime = qFloor(SonicationPeriod - DutyOnTime);
    CycleNum = qFloor(SonicationTime*1000 / DutyOnTime);

    //this->accept();

    real_T Voltage[112],AngleT[112];
    int i;
    PhaseInfo(1,Focus_X[CurrentSpotNum],Focus_Y[CurrentSpotNum],Focus_Z[CurrentSpotNum],Voltage,AngleT);
    for (i = 0; i < NumOfTransducer; i++)
    {
        sendPhase(i,(quint8)AngleT[i]);
        loadPhase();
    }
    enableDO();
    startSending();
}

void StaticDO::ButtonCancelClicked()
{
    this->reject();
}

void StaticDO::checkError(ErrorCode errorCode)
{
    if (errorCode != Success) {
        QString message = "Sorry, there are some errors occurred, Error Code: 0x" +
            QString::number(errorCode, 16).right(8);
        QMessageBox::information(NULL,"Warning Information", message,QMessageBox::Ok);
    }
}
