#include "mainwindow.h"
#include "lib/logging_define.cpp"
#include <QApplication>
#include <QDebug>
#include <QThread>
#include <time.h>

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logMessageOutput);
    QApplication a(argc, argv);

    int debugFlag = 2;
    if (debugFlag == 0)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }

    if (debugFlag == 1)
    {
        PowerAmp* p = new PowerAmp;
        int channel = 3;
        double volt = 7.1;
        bool ok;
        ok = p->startSinglePowerAmp(channel,volt);
        ok = p->echoPowerAmp(channel);
        ok = p->resetSinglePowerAmp(channel);
    }

    if (debugFlag == 2)
    {
        PowerAmp* p = new PowerAmp;
        int runTimes = 1;
        while(true){
        qCDebug(Test_module()) << Test_module().categoryName() <<":" << "Starting testing";
        qCWarning(Test_module()) << Test_module().categoryName() <<":" << "Starting testing";
        qCWarning(Test_module()) << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ").toLocal8Bit() << "    Current run times: " << runTimes;

    //To generate random channel numbers between the range of 1-112
    bool checkUnique(int random, int channel[],int n);
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second()*1000);

    int i, channel[12];
    i = 0;
    while (i < 12)
    {
        int random = qrand()%113;
        if (checkUnique(random,channel,i))
        {
            if (random)
            {
                bool isEscape = (random == 30 || random == 49 || random == 108);
                if (!isEscape)
                {
                    channel[i] = random;
                    qCDebug(Test_module()) << "Number of channel" << i+1 << ":" << channel[i];
                    i += 1;
                }
            }
        }

    }
    qCDebug(Test_module())<<"======================================";

    //to generate random voltage values between the range of 0-18 V
    double volt[12];
    i = 0;
    while (i < 12)
    {
        int random = qrand()%181;
        if (random)
        {
            volt[i] = (double)random;
            i += 1;
        }
    }

    for (i = 0; i < 12; i++)
    {
        volt[i] = (double)volt[i]/ 10;
        qCDebug(Test_module()) << "Voltage value" << i+1 << ":" << volt[i];
    }
    qCDebug(Test_module())<<"======================================";

    //int channel[12] = {110,6,3,73,65,1,79,74,103,37,45,111};
    //double volt[12] = {16.8,17.2,7.1,1.9,9.2,11,17,15,1.6,1.2,5.4,8.5};
    //int i;
    //start setting single power amplifier
    qCDebug(Test_module()) << "startSinglePowerAmp: ";
    bool success;
    for (i = 0; i < 12; i++)
    {
        QThread::msleep(100);
        success = p->startSinglePowerAmp(channel[i], volt[i]);
        qCDebug(Test_module()) << "Result" << i+1 << ":" << success;
        if (!success)
            qCWarning(Test_module()) << "Start single result" << i+1 << ":" << success;
    }
    qCDebug(Test_module())<<"======================================";

    //start echoing voltage value
    qCDebug(Test_module()) << "echoPowerAmp: ";
    double echoVolt;
    for (i = 0; i < 12; i++)
    {
        QThread::msleep(100);
        echoVolt = p->echoPowerAmp(channel[i]);
        qCDebug(Test_module()) << "Echo Volt" << i+1 << ":" << echoVolt;
        if (!success)
            qCWarning(Test_module()) << "Echo single result" << i+1 << ":" << success;
    }
    qCDebug(Test_module())<<"======================================";

    //starting reseting single power amplifier
    qCDebug(Test_module()) << "resetSinglePowerAmp: ";
    for (i = 0; i < 12; i++)
    {
        QThread::msleep(100);
        success = p->resetSinglePowerAmp(channel[i]);
        qCDebug(Test_module()) << "Result" << i+1 << ":" << success;
        if (!success)
            qCWarning(Test_module()) << "Reset single result" << i+1 << ":" << success;
    }
    qCDebug(Test_module())<<"======================================";

    //start setting all power amplifiers
    qCDebug(Test_module()) << "startAllPowerAmp: ";
    double time_Start = (double)clock();
    success = p->startAllPowerAmp(volt[6]);
    double time_End = (double)clock();
    qCDebug(Test_module()) << "Result" << ":" << success;
    if (!success)
        qCWarning(Test_module()) << "Start all result:" << success;
    qCWarning(Test_module()) <<"startAllPowerTime: "<< (time_End - time_Start) / 1000.0 << "s";
    qCDebug(Test_module())<<"======================================";

    //start reseting all power amplifiers
    qCDebug(Test_module()) << "resetAllPowerAmp: ";
    time_Start = (double)clock();
    success = p->resetAllPowerAmp();
    time_End = (double)clock();
    qCDebug(Test_module()) << "Result" << ":" << success;
    if (!success)
        qCWarning(Test_module()) << "Reset all result:" << success;
    qCWarning(Test_module()) <<"resetAllPowerAmpTime: "<< (time_End - time_Start) / 1000.0 << "s";
    qCDebug(Test_module())<<"======================================";

    //end testing
    qCDebug(Test_module()) << Test_module().categoryName() <<":" << "End testing";
    qCDebug(Test_module())<<"======================================";
    qCWarning(Test_module()) << Test_module().categoryName() <<":" << "End testing";
    qCWarning(Test_module())<<"======================================";
    runTimes += 1;
    }
    }
    return a.exec();
}

bool checkUnique(int random, int data[],int n)
{
    bool isUnique = true;
    for(int i = 0; i < n; i++)
    {
        if (random == data[i])
        {
            isUnique = false;
            break;
        }
    }
    return isUnique;
}
