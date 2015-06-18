#include "mainwindow.h"
#include "printwindow.h"
#include <QApplication>
#include <QPrintPreviewDialog>
#include <QPrinter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrintWindow printpdf;
    printpdf.generateHtml();

    return a.exec();
}
