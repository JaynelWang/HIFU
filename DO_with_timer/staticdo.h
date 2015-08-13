#ifndef STATICDO
#define STATICDO

#include <QObject>
#include <QDialog>
#include <QString>
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
    void writeData(int port, quint8 state);

signals:
    void errorOccurred(QString error);

private:
    InstantDoCtrl *m_instantDOCtrl;
    QString m_deviceName;
    void selectDevice(QString deviceName);
    void checkError(ErrorCode errorCode);
};

#endif // STATICDO

