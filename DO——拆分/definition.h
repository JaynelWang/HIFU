#ifndef DEFINITION
#define DEFINITION

#include "PhaseInfo/PhaseInfo.h"
#include <QList>
#define DEVICENAME "USB-4751,BID#0"
typedef QList<real_T> coordinate;
typedef uint8_T focusNum;

struct limitForLineEdit
{
    int sonicationTime_LL;
    int sonicationTime_UL;
    int sonicationPeriod_LL;
    int sonicationPeriod_UL;
    int dutyCycle_LL;
    int dutyCycle_UL;
    int coolingTime_LL;
    int coolingTime_UL;
};
 const limitForLineEdit validatorOfLineEdit = {6,20,1,1000,1,100,1,500};

struct portsValue
{
    int portForChannel;
    int portForPhase;
    int portForLoad;
    int portForEnable;
    int portForDisable;
};
const portsValue portValue = {4,5,3,3,3};

struct spotCoordinate
{
    coordinate focus_X;
    coordinate focus_Y;
    coordinate focus_Z;
};

struct treatmentParameter
{
    int sonicationTime;
    int sonicationPeriod;
    int dutyCycle;
    int coolingTime;
};
const treatmentParameter defaultParameter = {5,500,100,300};

struct treatmentPlan
{
    QList<spotCoordinate> spot;
    QList<treatmentParameter> parameters;
};

#endif // DEFINITION

