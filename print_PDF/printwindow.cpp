#include "printwindow.h"
#include <QDateTime>

PrintWindow::PrintWindow()
{
    PatientInfo PatientInfo2Print = {"Mary",60,10,10,10};
    patientList << PatientInfo2Print;
    TreatmentPlan TP = {0,0,140,7.8,15,500,50,300};
    allTP << TP;
}

PrintWindow::~PrintWindow()
{
//delete printer;
}


void PrintWindow::generateHtml()
{
    QString html;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    html +="<h2 align=\"center\">"+QStringLiteral("TREATMENT PLAN") + "</h2>"
           "<h4 align=\"center\">"+current_date+"<h4>"
           "<h4 align=\"center\">"+patientList[0].PatientName+"<h4>"
           "<h4 align=\"center\">"+QString::number(allTP[0].Spot_Z)+"<h4>";
    printTP(html);
}

void PrintWindow::printTP(const QString &html)
{
    QPrintDialog printDialog(&printer);
    if (printDialog.exec()) {
        QTextDocument textDocument;
        textDocument.setHtml(html);
        textDocument.print(&printer);
    }
}
