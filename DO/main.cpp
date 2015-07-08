#include "mainwindow.h"
#include "staticdo.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StaticDO DO;
    int resultDO = DO.exec();
    if (resultDO == QDialog::Rejected)
    {
        a.exit(0);
        return 0;
    }

    return a.exec();
}
