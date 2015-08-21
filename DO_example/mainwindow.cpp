#include "mainwindow.h"
#include <QIntValidator>
#include <QString>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //set the layout of the GUI
    this->setWindowTitle("StaticDO");

    sonicationTime_label = new QLabel(this);
    sonicationTime_edit = new QLineEdit(this);
    sonicationTimeUnit_label = new QLabel(this);
    sonicationTime_layout = new QHBoxLayout(this);
    sonicationTime_label->setText("SonicationTime:");
    sonicationTime_edit->setText(QString::number(SONICATIONTIME_DEFAULT));
    sonicationTimeUnit_label->setText("s");
    sonicationTime_layout->addWidget(sonicationTime_label);
    sonicationTime_layout->addWidget(sonicationTime_edit);
    sonicationTime_layout->addWidget(sonicationTimeUnit_label);

    sonicationPeriod_label = new QLabel(this);
    sonicationPeriod_edit = new QLineEdit(this);
    sonicationPeriodUnit_label = new QLabel(this);
    sonicationPeriod_layout = new QHBoxLayout(this);
    sonicationPeriod_label->setText("SonicationPeriod:");
    sonicationPeriod_edit->setText(QString::number(SONICATIONPERIOD_DEFAULT));
    sonicationPeriodUnit_label->setText("ms");
    sonicationPeriod_layout->addWidget(sonicationPeriod_label);
    sonicationPeriod_layout->addWidget(sonicationPeriod_edit);
    sonicationPeriod_layout->addWidget(sonicationPeriodUnit_label);

    dutyCycle_label = new QLabel(this);
    dutyCycle_edit = new QLineEdit(this);
    dutyCycleUnit_label = new QLabel(this);
    dutyCycle_layout = new QHBoxLayout(this);
    dutyCycle_label->setText("DutyCycle:");
    dutyCycle_edit->setText(QString::number(DUTYCYCLE_DEFAULT));
    dutyCycleUnit_label->setText("%");
    dutyCycle_layout->addWidget(dutyCycle_label);
    dutyCycle_layout->addWidget(dutyCycle_edit);
    dutyCycle_layout->addWidget(dutyCycleUnit_label);

    coolingTime_label = new QLabel(this);
    coolingTime_edit = new QLineEdit(this);
    coolingTimeUnit_label = new QLabel(this);
    coolingTime_layout = new QHBoxLayout(this);
    coolingTime_label->setText("CoolingTime:");
    coolingTime_edit->setText(QString::number(COOLINGTIME_DEFAULT));
    coolingTimeUnit_label->setText("s");
    coolingTime_layout->addWidget(coolingTime_label);
    coolingTime_layout->addWidget(coolingTime_edit);
    coolingTime_layout->addWidget(coolingTimeUnit_label);

    ok_btn = new QPushButton(this);
    pause_btn = new QPushButton(this);
    restart_btn = new QPushButton(this);
    cancel_btn = new QPushButton(this);
    button_layout = new QHBoxLayout(this);
    ok_btn->setText("OK");
    pause_btn->setText("Pause");
    restart_btn->setText("Restart");
    cancel_btn->setText("Cancel");
    button_layout->addWidget(ok_btn);
    button_layout->addWidget(pause_btn);
    button_layout->addWidget(restart_btn);
    button_layout->addWidget(cancel_btn);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(sonicationTime_layout);
    mainLayout->addLayout(sonicationPeriod_layout);
    mainLayout->addLayout(dutyCycle_layout);
    mainLayout->addLayout(coolingTime_layout);
    mainLayout->addLayout(button_layout);
    QWidget * widget = new QWidget (this) ;
    widget->setLayout(mainLayout) ;
    this->setCentralWidget(widget) ;


    //validators for lineedits
    QIntValidator *validatorForSonicationTime = new QIntValidator(SONICATIONTIME_LL,SONICATIONPERIOD_UL,this);
    sonicationTime_edit->setValidator(validatorForSonicationTime);
    QIntValidator *validatorForSonicationPeriod = new QIntValidator(SONICATIONPERIOD_LL,SONICATIONPERIOD_UL,this);
    sonicationPeriod_edit->setValidator(validatorForSonicationPeriod);
    QIntValidator *validatorForDutyCycle = new QIntValidator(DUTYCYCLE_LL,DUTYCYCLE_UL,this);
    dutyCycle_edit->setValidator(validatorForDutyCycle);
    QIntValidator *validatorForCoolingTime = new QIntValidator(COOLINGTIME_LL,COOLINGTIME_UL,this);
    coolingTime_edit->setValidator(validatorForCoolingTime);


    //connecting signals and slots
    connect(ok_btn, SIGNAL(clicked()), SLOT(buttonOKClicked()));
    connect(pause_btn,SIGNAL(clicked()),SLOT(buttonPauseClicked()));
    connect(restart_btn, SIGNAL(clicked()), SLOT(buttonRestartClicked()));
    connect(cancel_btn, SIGNAL(clicked()), SLOT(buttonCancelClicked()));
    connect(&m_CtrlTimer,SIGNAL(timeout()),SLOT(CtrlTimerFcn()));

    //initialize m_DOController and other members
    m_DOController = new DOController;   
    m_currentCycleCount = 0;
    m_currentSpotCount = 0;
    m_transducerCount = 112;
    m_CtrlTimer.setSingleShot(true);
}

MainWindow::~MainWindow()
{
    if (m_CtrlTimer.isActive())
        m_CtrlTimer.stop();
}

void MainWindow::buttonOKClicked()
{
    m_sonicationParameter.time = sonicationTime_edit->text().toInt();
    m_sonicationParameter.period = sonicationPeriod_edit->text().toInt();
    m_sonicationParameter.dutyCycle = dutyCycle_edit->text().toInt();
    m_sonicationParameter.coolingTime = coolingTime_edit->text().toInt();
    m_dutyOnTime = qFloor(m_sonicationParameter.period * m_sonicationParameter.dutyCycle / 100);
    m_dutyOffTime = qFloor(m_sonicationParameter.period - m_dutyOnTime);
    m_cycleCount = qFloor(m_sonicationParameter.time * 1000 / m_dutyOnTime);
    startSending();
}

void MainWindow::buttonCancelClicked()
{
    this->close();
}

void MainWindow::buttonRestartClicked()
{
    if (m_CtrlTimer.isActive())
        m_CtrlTimer.stop();
    m_currentCycleCount = 0;
    m_currentSpotCount = 0;
    startSending();
}

void MainWindow::buttonPauseClicked()
{
    if (m_CtrlTimer.isActive())
        m_CtrlTimer.stop();
    m_currentCycleCount = 0;
    m_currentSpotCount = 0;
}

void MainWindow::startSending()
{
    real_T Voltage[112], AngleT[112], temp;
    spotForCount spotCount = 1;
    int i;
    PhaseInfo(spotCount,m_spot[m_currentSpotCount].spot_X,m_spot[m_currentSpotCount].spot_Y,m_spot[m_currentSpotCount].spot_Z,Voltage,AngleT);
    //exchange the phases of channel 35 and 36
    temp = AngleT[34];
    AngleT[34] = AngleT[35];
    AngleT[35] = temp;

    //start sending
    for (i = 0; i < m_transducerCount; i++)
    {
        m_DOController->sendPhase(i,(quint8)AngleT[i]);
        m_DOController->loadPhase();
    }
    m_DOController->enableDO();

    m_timerFlag = 0;
    m_CtrlTimer.start(m_dutyOnTime);
}

void MainWindow::CtrlTimerFcn()
{
    switch (m_timerFlag){
        case 0:
            qDebug("timeOn: %d",m_currentCycleCount + 1);
            m_DOController->disableDO();
            m_timerFlag = 1;
            m_CtrlTimer.start(m_dutyOffTime);
            break;
        case 1:
            m_currentCycleCount += 1;
            qDebug("timeOff: %d",m_currentCycleCount);
            if (m_currentCycleCount < m_cycleCount)
            {
                m_DOController->enableDO();
                m_timerFlag = 0;
                m_CtrlTimer.start(m_dutyOnTime);
            }
            else if (m_currentCycleCount = m_cycleCount)
            {
                m_timerFlag = 2;
                m_CtrlTimer.start(m_sonicationParameter.coolingTime*1000);
            }
            break;
        case 2:
            m_currentSpotCount += 1;
            qDebug("timeCool: %d",m_currentSpotCount);
            m_currentCycleCount = 0;

            if (m_currentSpotCount < m_spotCount)
                startSending();
            else if (m_currentSpotCount = m_spotCount)
                {
                    m_DOController->~DOController();
                    exit(0);
                }
            break;

        }
}

void MainWindow::setSpot(QList<SpotCoordinate> spot)
{
    m_spot = spot;
    m_spotCount = m_spot.size();
}

int MainWindow::getSpotCount()
{
    return this->m_spotCount;
}
