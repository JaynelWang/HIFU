#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    spotCoordinate focus;
    focus.focus_X << 0 << 0;
    focus.focus_Y << 0.005 << 0.006;
    focus.focus_Z << 0.14 << 0.15;
    int spotNum = focus.focus_X.size();

    MainWindow w;
    w.m_DOController->setFocusCoordinate(focus);
    w.m_DOController->setSpotNum(spotNum);

    w.show();

    return a.exec();
}
