#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QObject>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QString>
#include <QPainter>
#include <QTextDocument>

struct PatientInfo
    {QString PatientName;
     int PatientAge;
     double TargetSize_X;
     double TargetSize_Y;
     double TargetSize_Z;
    };

struct TreatmentPlan
    {double Spot_X;
     double Spot_Y;
     double Spot_Z;
     double voltage;
     int SonicationTime;
     int SonicationPeriod;
     int DutyCycle;
     int CoolingTime;
    };

class PrintWindow
{
public:
    PrintWindow();
    ~PrintWindow();
    QPrinter printer;
    PatientInfo PatientInfo2Print;
    TreatmentPlan TP[5];
    void generateHtml(PatientInfo PatientInfo2Print, TreatmentPlan TP[]);
    void printTP(const QString &html);
};

#endif // PRINTWINDOW_H
