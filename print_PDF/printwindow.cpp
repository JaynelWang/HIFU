#include "printwindow.h"
#include <QDateTime>
#include <QPrinter>
#include <QTextBlock>

PrintWindow::PrintWindow()
{
    PatientInfo PatientInfo2Print = {"Mary",60,10,10,10};
    PatientList << PatientInfo2Print;
    TreatmentPlan TP[]={{0,0,140,7.8,15,500,50,300},{-1.04,5.91,140,7.8,15,500,50,300},
                        {1.04,-5.91,140,7.8,15,500,50,300},{5.91,1.04,140,7.8,15,500,50,300},{-5.91,-1.04,140,7.8,15,500,50,300}};
    for(int i=0; i<sizeof(TP)/48; i++)
        {
            allTP << TP[i];
        }
}

PrintWindow::~PrintWindow()
{
printer.~QPrinter();
}


void PrintWindow::generateHtml()
{
    QString html;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QStringList title;
        title.push_back(QStringLiteral("Spot"));
        title.push_back(QStringLiteral("Voltage (V)"));
        title.push_back(QStringLiteral("SonicationTime (s)"));
        title.push_back(QStringLiteral("SonicationPeriod (ms)"));
        title.push_back(QStringLiteral("DutyCycle (%)"));
        title.push_back(QStringLiteral("CoolingTime (s)"));

    html +="<h2 align=\"center\">"+QStringLiteral("TREATMENT PLAN") + "</h2>"
           "<h4 align=\"center\">"+current_date+"</h4>"
           "<h3><U><i><align=\"left\">"+QString("Patient Information:")+"</i></U></h3>"
           "<h4 align=\"left\">"+QString("%1 %2").arg(QStringLiteral("Patient Name:")).arg(PatientList[0].PatientName)+ "</h4>"
           "<h4 align=\"left\">"+QString("%1 %2").arg(QStringLiteral("Patient Age:")).arg(QString::number(PatientList[0].PatientAge))+ "</h4>"
           "<h4 align=\"left\">"+QString("%1 %2*%3*%4 mm^3").arg(QStringLiteral("Patient's Target Size:"))
                                                            .arg(QString::number(PatientList[0].TargetSize_X))
                                                            .arg(QString::number(PatientList[0].TargetSize_Y))
                                                            .arg(QString::number(PatientList[0].TargetSize_Z))+ "</h4>"
           "<h3><U><i><align=\"left\">"+QString("Specific Plan:")+"</i></U></h3>"
           "<table width=\"100%\" border=1 cellspacing=0>\n"
           "<tr align=center bgcolor=lightgray>";

    for(int i=0;i<title.count();i++)
        {
            html += QString("<th B>%1</th>").arg(title.at(i));
        }
        html += "</tr>";
        for(int i=0; i<sizeof(allTP)+1; i++)
        {
         html += "<tr>"
                 "<td align=center>("+QString("%1,%2,%3").arg(QString::number(allTP[i].Spot_X))
                                                         .arg(QString::number(allTP[i].Spot_Y))
                                                         .arg(QString::number(allTP[i].Spot_Z))+")</td>"
                 "<td align=center>"+QString::number(allTP[i].voltage)+"</td>"
                 "<td align=center>"+QString::number(allTP[i].SonicationTime)+"</td>"
                 "<td align=center>"+QString::number(allTP[i].SonicationPeriod)+"</td>"
                 "<td align=center>"+QString::number(allTP[i].DutyCycle)+"</td>"
                 "<td align=center>"+QString::number(allTP[i].CoolingTime)+"</td>"
                 "</tr>";
         }
    html += "</table>";
    printTP(html);
}

void PrintWindow::printTP(const QString &html)
{
    QPrintDialog printDialog(&printer);
    printer.setResolution(QPrinter::HighResolution);
    if (printDialog.exec()) {
        QTextDocument textDocument;
        textDocument.setHtml(html);
        textDocument.print(&printer);
        textDocument.end();
    }
}
