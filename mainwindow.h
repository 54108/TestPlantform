#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serial.h"
#include "chart.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void updatelcdnumber(const QByteArray &data);
    ~MainWindow();

private slots:
    void resolveData(const QByteArray &data);
    void onComboBoxCarChanged(int index);
    void onDailChanged(int value);

private:
    Ui::MainWindow *ui;
    SerialThread *serialThread;
    volatile int min = 0, max = 0, speed = 0;
    volatile float wheelSpeed = 0, axisTorque = 0, acceleration = 0, busCurrent = 0, busVoltage = 0, phaseCurrent = 0, phaseVoltage = 0, power = 0, efficiency = 0;
    const QByteArray signal = QByteArray("\x77\x01\x3C\x22", 4);
    QByteArray ctrl = QByteArray("\x77\x01\x3C\x22", 4);
};
#endif // MAINWINDOW_H
