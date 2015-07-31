#include "mainwindow.h"
#include "poweramp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    PowerAmp* p = new PowerAmp;
    int PowerAmpId = 7;
    double Volt = 14.4;
    bool ok = p->resetSinglePowerAmp(PowerAmpId);
    int b = 1;

    return a.exec();
}
