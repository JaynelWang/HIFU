#include "mainwindow.h"
#include "printwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PrintWindow printpdf;
    printpdf.printFlowerGuide(printpdf.entries);

    return a.exec();
}
