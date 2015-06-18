#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QObject>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QString>
#include <QPainter>
#include <QTextDocument>
#include <QList>


class PrintWindow
{
public:
    PrintWindow();
    ~PrintWindow();
    QPrinter printer;
    void generateHtml();
    void printTP(const QString &html);

private:
    struct PatientInfo
        {QString PatientName;
         int PatientAge;
         double TargetSize_X;
         double TargetSize_Y;
         double TargetSize_Z;
        };
    QList<PatientInfo> patientList;

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
    QList<TreatmentPlan> allTP;
};

#endif // PRINTWINDOW_H
