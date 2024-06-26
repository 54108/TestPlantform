#ifndef SERIAL_H
#define SERIAL_H
#include <QThread>
#include <QtLogging>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "mainwindow.h"

class SerialThread : public QThread {
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = nullptr);
    ~SerialThread();
    void run() override;
    void init(QSerialPort * sp);

signals:
    void readydata(const QByteArray &data);

private:
    QSerialPort *serial;
    QByteArray data;
};

#endif // SERIAL_H
