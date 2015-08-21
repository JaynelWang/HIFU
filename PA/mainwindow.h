#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "poweramp.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

Q_DECLARE_LOGGING_CATEGORY(Test_module)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    PowerAmp* m_PAController;

signals:
    void readDone(QByteArray readData);

private slots:
    void handleWrite();
    void handleReadyRead();
    void handleReadDone(QByteArray readData);
    void handleTimeout();

private:
    Ui::MainWindow *ui;
    QByteArray m_readData;
    QTimer m_timer;
    void startTimer(QTimer &timer);
};

#endif // MAINWINDOW_H

