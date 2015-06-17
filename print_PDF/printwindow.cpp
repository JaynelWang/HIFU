#include "printwindow.h"
#include <QDateTime>

PrintWindow::PrintWindow()
{
    PatientInfo2Print = {"Mary",60,10,10,10};
    TP[] = {{0,0,140,7.8,15,500,50,300},{-1.04,5.91,140,7.8,15,500,50,300},{1.04,-5.91,140,7.8,15,500,50,300},{5.91,1.04,140,7.8,15,500,50,300},{-5.91,-1.04,140,7.8,15,500,50,300}};
}

PrintWindow::~PrintWindow()
{
//delete printer;
}


void PrintWindow::generateHtml(PatientInfo PatientInfo2Print, TreatmentPlan TP[])
{
    QString html;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    html +="<h2 align=\"center\">"+QStringLiteral("TREATMENT PLAN") + "</h2>"
           "<h4 align=\"center\">"+current_date+"<h4>"
           "<h4 align=\"center\">"+PatientInfo2Print.PatientName+"<h4>"
           "<h4 align=\"center\">"+QString::number(TP[0].Spot_Z)+"<h4>";
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
