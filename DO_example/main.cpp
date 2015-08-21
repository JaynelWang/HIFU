#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<SpotCoordinate> spot;
    SpotCoordinate spots[] = {{0,0.005,0.14},{0,0.006,0.15}};
    int i,s;
    s = sizeof(spots) / sizeof(spots[0]);
    for(i = 0; i < s; i++)
        spot << spots[i];

    MainWindow w;
    w.setSpot(spot);
    w.show();

    return a.exec();
}
