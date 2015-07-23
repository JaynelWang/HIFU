#ifndef STATICDO
#define STATICDO

#include <QObject>
#include <QDialog>
#include "PhaseInfo/PhaseInfo.h"
#include "inc/bdaqctrl.h"
#include "definition.h"

using namespace Automation::BDaq;

class StaticDO : public QObject
{
    Q_OBJECT
public:
    StaticDO(QObject *parent = 0);
    ~StaticDO();
    int m_port;
    quint8 m_state;
    void setPort(int port);
    int getPort();
    void setState(quint8 state);
    quint8 getState();
    void writeData(int port, quint8 state);

private:
    InstantDoCtrl *m_instantDOCtrl;
    QString m_deviceName;
    InstantDoCtrl * selectDevice(QString deviceName);
    void checkError(ErrorCode errorCode);

};

#endif // STATICDO

