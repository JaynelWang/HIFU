#include "mainwindow.h"
#include "poweramp.h"
#include "logging_define.cpp"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logMessageOutput);
    QApplication a(argc, argv);

    int debugFlag = 0;
    if (debugFlag == 0)
    {
        MainWindow w;
        w.show();
    }

    if (debugFlag == 1)
    {
        PowerAmp* p = new PowerAmp;
        int channel = 3;
        double volt = 7.1;
        bool ok;
        ok = p->startSinglePowerAmp(channel,volt);
    }

    if (debugFlag == 2)
    {
        PowerAmp* p = new PowerAmp;
        qCDebug(Test_module()) << Test_module().categoryName() <<":" << "Starting testing";
/*
    //To generate random channel numbers between the range of 1-112
    bool checkUnique(int random, int channel[],int n);
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second()*1000);

    int i, channel[12];
    i = 0;
    while (i < 12)
    {
        int random = qrand()%112;
        if (checkUnique(random,channel,i))
        {
            if (random)
            {
                channel[i] = random;
                qCDebug(Test_module()) << "Number of channel" << i+1 << ":" << channel[i];
                i += 1;
            }
            else
            {
                i -= 1;
                break;
            }
        }

    }
    qCDebug(Test_module())<<"======================================";

    //to generate random voltage values between the range of 0-18 V
    double volt[12];
    i = 0;
    while (i < 12)
    {
        int random = qrand()%180;
        if (random)
        {
            volt[i] = (double)random;
            i += 1;
        }
        else
        {
            i -= 1;
            break;
        }

    }

    for (i = 0; i < 12; i++)
    {
        volt[i] = (double)volt[i]/ 10;
        qCDebug(Test_module()) << "Voltage value" << i+1 << ":" << volt[i];
    }
    qCDebug(Test_module())<<"======================================";
*/
    int channel[12] = {110,6,3,73,65,1,79,74,103,37,45,111};
    double volt[12] = {16.8,17.2,7.1,1.9,9.2,11,17,15,1.6,1.2,5.4,8.5};
    int i;
    //start setting single power amplifier
    qCDebug(Test_module()) << "startSinglePowerAmp: ";
    bool success;
    for (i = 0; i < 12; i++)
    {
        success = p->startSinglePowerAmp(channel[i], volt[i]);
        qCDebug(Test_module()) << "Result" << i+1 << ":" << success;
    }
    qCDebug(Test_module())<<"======================================";
/*
    //start echoing voltage value
    qCDebug(Test_module()) << "echoPowerAmp: ";
    double echoVolt;
    for (i = 0; i < 12; i++)
    {
        echoVolt = p->echoPowerAmp(channel[i]);
        qCDebug(Test_module()) << "Echo Volt" << i+1 << ":" << echoVolt;
    }
    qCDebug(Test_module())<<"======================================";

    //starting reseting single power amplifier
    qCDebug(Test_module()) << "resetSinglePowerAmp: ";
    for (i = 0; i < 12; i++)
    {
        success = p->resetSinglePowerAmp(channel[i]);
        qCDebug(Test_module()) << "Result" << i+1 << ":" << success;
    }
    qCDebug(Test_module())<<"======================================";

    //start setting all power amplifiers
    qCDebug(Test_module()) << "startAllPowerAmp: ";
    success = p->startAllPowerAmp(volt[6]);
    qCDebug(Test_module()) << "Result" << ":" << success;
    qCDebug(Test_module())<<"======================================";

    //start reseting all power amplifiers
    qCDebug(Test_module()) << "resetAllPowerAmp: ";
    success = p->resetAllPowerAmp();
    qCDebug(Test_module()) << "Result" << ":" << success;
    qCDebug(Test_module())<<"======================================";

    //end testing
    qCDebug(Test_module()) << Test_module().categoryName() <<":" << "End testing";
*/
    }
    return a.exec();
}

bool checkUnique(int random, int data[],int n)
{
    bool isUnique = true;
    int i;
    for(i = 0; i < n; i++)
    {
        if (random == data[i])
            isUnique = false;
    }
    return isUnique;
}
