#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QObject>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QString>
#include <QPainter>
#include <QTextDocument>

class PrintWindow
{
public:
    PrintWindow();
    ~PrintWindow();
    void printFlowerGuide(const QStringList &entries);
    void printHtml(const QString &html);
    QPrinter printer;
    QStringList entries;
};

#endif // PRINTWINDOW_H
