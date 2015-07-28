#include "mainwindow.h"
#include "definition.h"
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
    restart_btn = new QPushButton(this);
    cancel_btn = new QPushButton(this);
    button_layout = new QHBoxLayout(this);
    ok_btn->setText("OK");
    restart_btn->setText("Restart");
    cancel_btn->setText("Cancel");
    button_layout->addWidget(ok_btn);
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
    connect(restart_btn, SIGNAL(clicked()), SLOT(buttonRestartClicked()));
    connect(cancel_btn, SIGNAL(clicked()), SLOT(buttonCancelClicked()));

    //initialize m_DOController
    m_DOController = new DOController;   
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonOKClicked()
{
    m_DOController->m_sonicationParameter.time = sonicationTime_edit->text().toInt();
    m_DOController->m_sonicationParameter.period = sonicationPeriod_edit->text().toInt();
    m_DOController->m_sonicationParameter.dutyCycle = dutyCycle_edit->text().toInt();
    m_DOController->m_sonicationParameter.coolingTime = coolingTime_edit->text().toInt();
    m_DOController->m_dutyOnTime = qFloor(m_DOController->m_sonicationParameter.period * m_DOController->m_sonicationParameter.dutyCycle / 100);
    m_DOController->m_dutyOffTime = qFloor(m_DOController->m_sonicationParameter.period - m_DOController->m_dutyOnTime);
    m_DOController->m_cycleCount = qFloor(m_DOController->m_sonicationParameter.time * 1000 / m_DOController->m_dutyOnTime);
    m_DOController->startSending();
}

void MainWindow::buttonCancelClicked()
{
    this->close();
}

void MainWindow::buttonRestartClicked()
{
    m_DOController->restart();
}
