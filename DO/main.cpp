#include "mainwindow.h"
#include "staticdo.h"
#include "PhaseInfo/PhaseInfo.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    uint8_T NumFocus = 1;
    real_T PosXFocus[] = {0,0};
    real_T PosYFocus[] = {0.005,0.006};
    real_T PosZFocus[] = {0.14,0.15};
    int SpotNo = sizeof(PosXFocus) / sizeof(PosXFocus[1]);

    int NumOfTransducer = 112;

    StaticDO DO;
    /* //For test:
    DO.setKey(3);
    DO.setState((quint8)192);
    int key = DO.getKey();
    quint8 state = DO.getState();
    DO.writeData(key,state);*/

    DO.setSpotNum(SpotNo);
    int resultDO = DO.exec();
    if (resultDO == QDialog::Rejected)
    {
        a.exit(0);
        return 0;
    }
    else if (resultDO == QDialog::Accepted)
    {real_T Voltage[112],AngleT[112];
    int i,j;
    for (i = 1; i <= SpotNo; i++)
        {PhaseInfo(NumFocus,PosXFocus[i],PosYFocus[i],PosZFocus[i],Voltage,AngleT);
        for (j = 1; j <= NumOfTransducer; j++)
        {
            DO.sendPhase(j,(quint8)AngleT[j]);
            DO.loadPhase();
        }

        DO.enableDO();
        DO.startSending();
        }
    }
    return a.exec();
}
