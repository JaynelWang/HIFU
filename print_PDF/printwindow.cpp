#include "printwindow.h"

PrintWindow::PrintWindow()
{
entries<<"Miltonopsis santanae:dangerous"<<"Cactus:endurance"<<"Lily:purity";
}

PrintWindow::~PrintWindow()
{

}


void PrintWindow::printFlowerGuide(const QStringList &entries)
{
    QString html;
    foreach (QString entry, entries) {
        QStringList fields = entry.split(":");
        QString title = QString(fields[0]).toHtmlEscaped();
        QString body = QString(fields[1]).toHtmlEscaped();
        html += "<table width=\"100%\" border=1 cellspacing=0>\n"
                "<tr><td bgcolor=\"lightgray\"><font size=\"+1\">"
                "<b><i>" + title + "</i></b></font>\n<tr><td>" + body
                + "\n</table>\n<br>\n";
    }
    printHtml(html);
}

void PrintWindow::printHtml(const QString &html)
{
    QPrintDialog printDialog(&printer);
    if (printDialog.exec()) {
        QTextDocument textDocument;
        textDocument.setHtml(html);
        textDocument.print(&printer);
    }
}
