#include "staticdo.h"
#include <QMessageBox>
#include <QtGui>

StaticDO::StaticDO(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));

    Key = 0;
    State = (quint8)0;
    SpotNum = 5;
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
    DeviceName = "USB-4704,BID#0";
    std::wstring description = DeviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    instantDOCtrl = AdxInstantDoCtrlCreate();

    ErrorCode errorCode = Success;
    errorCode = instantDOCtrl->setSelectedDevice(selected);
    checkError(errorCode);
}

void StaticDO::startSending()
{
    setState((quint8)1);
    writeData(Key,State);
    TimerFlag = 0;
    CtrlTimer.singleShot(DutyOnTime,this,SLOT(CtrlTimerFcn()));
    CtrlTimer.start();
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

void StaticDO::CtrlTimerFcn()
{
    switch (TimerFlag){
            case 0:
                qDebug("timeOn: %d",CurrentCycleNum);
                setState((quint8)0);
                writeData(Key,State);
                TimerFlag = 1;
                CtrlTimer.singleShot(DutyOffTime,this,SLOT(CtrlTimerFcn()));
                CtrlTimer.start();
                break;
            case 1:
                CurrentCycleNum += 1;
                qDebug("timeOff: %d",CurrentCycleNum);
                if (CurrentCycleNum < CycleNum)
                {
                    setState((quint8)1);
                    writeData(Key,State);
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
                if (CurrentSpotNum < SpotNum)
                {
                    CurrentCycleNum = 0;
                    setState((quint8)1);
                    writeData(Key,State);
                    TimerFlag = 0;
                    CtrlTimer.singleShot(DutyOnTime,this,SLOT(CtrlTimerFcn()));
                    CtrlTimer.start();
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
