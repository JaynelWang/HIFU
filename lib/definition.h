#ifndef DEFINITION
#define DEFINITION

//#include "PhaseInfo/PhaseInfo.h"
#include <QList>
#define DEVICE_ID "USB-4751,BID#0"
#define SONICATIONTIME_LL 6
#define SONICATIONTIME_UL 20
#define SONICATIONPERIOD_LL 1
#define SONICATIONPERIOD_UL 1000
#define DUTYCYCLE_LL 1
#define DUTYCYCLE_UL 100
#define COOLINGTIME_LL 1
#define COOLINGTIME_UL 500
#define SONICATIONTIME_DEFAULT 15
#define SONICATIONPERIOD_DEFAULT 500
#define DUTYCYCLE_DEFAULT 100
#define COOLINGTIME_DEFAULT 300
#define PORT_CHANNEL 4
#define PORT_PHASE 5
#define PORT_LOAD 3
#define PORT_ENABLE 3
#define PORT_DISABLE 3

struct SonicationParameter
{
    int time;
    int period;
    int dutyCycle;
    int coolingTime;
};

//struct TreatmentPlan
//{
//    QList<SpotCoordinate> spot;
//    QList<SonicationParameter> spotParameters;
//};

#endif // DEFINITION

