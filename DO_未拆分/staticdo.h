#ifndef STATICDO
#define STATICDO

#include <QString>
#include <QTimerEvent>
#include <QObject>
#include <QTimer>
#include <QDialog>
#include <QList>
#include "inc/bdaqctrl.h"
#include "ui_staticdo.h"
#include "PhaseInfo/PhaseInfo.h"

using namespace Automation::BDaq;

class StaticDO : public QDialog
{
    Q_OBJECT
public:
    StaticDO(QWidget *parent = 0);
    ~StaticDO();
    void startSending();
    void setSpotNum(int SpotNum);
    int getSpotNum();
    void setKey(int Key);
    int getKey();
    void setState(quint8 State);
    quint8 getState();
    void checkError(ErrorCode errorCode);
    void writeData(int Key, quint8 State);
    void sendPhase(int Channel, quint8 Phase);
    void loadPhase();
    void enableDO();
    void disableDO();

    QList<real_T> Focus_X;
    QList<real_T> Focus_Y;
    QList<real_T> Focus_Z;


private:
    Ui::Form ui;
    int Key;
    quint8 State;
    int DutyCycle;
    int SonicationPeriod;
    int SonicationTime;
    int CoolingTime;
    int DutyOnTime;
    int DutyOffTime;
    int TimerFlag;
    InstantDoCtrl *instantDOCtrl;
    QString DeviceName;
    QTimer CtrlTimer;
    int CycleNum;
    int SpotNum;
    int CurrentCycleNum;
    int CurrentSpotNum;
    int NumOfTransducer;
    void selectDevice();

private slots:
    void ButtonOKClicked();
    void ButtonCancelClicked();
    void CtrlTimerFcn();

};



#endif // STATICDO

