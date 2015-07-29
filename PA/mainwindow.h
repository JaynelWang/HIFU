#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "poweramp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleWrite();
    void handleRead(QByteArray readData);
    void handleError(QString errorString);

private:
    Ui::MainWindow *ui;
    PowerAmp * m_PAController;
};

#endif // MAINWINDOW_H
