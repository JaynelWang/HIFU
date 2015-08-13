#ifndef DOCONTROLLER
#define DOCONTROLLER

#include "staticdo.h"
#include <QObject>
#include <QTimer>

class DOController : public QObject
{
    Q_OBJECT
public:
    DOController(QWidget *parent = 0);
    ~DOController();
    void sendPhase(int channel, quint8 phase);
    void loadPhase();
    void enableDO();
    void disableDO();

private:
    StaticDO *m_DO;
};

#endif // DOCONTROLLER
