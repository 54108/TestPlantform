#ifndef SERIAL_H
#define SERIAL_H
#include <QtGlobal>
#include <QThread>
#include <QtLogging>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialThread : public QThread {
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = nullptr);
    ~SerialThread();
    void run() override;
    void init(QSerialPort * sp);
    void sendData(const QByteArray &data);

signals:
    void readydata(const QByteArray &data);

private:
    QSerialPort *serial;
    QByteArray data;
};

typedef struct msgData
{
    quint8 head = 0;
    quint8 ctrl = 0;
    qint16 speed = 0;
    float torque = 0;
    float busCurrent = 0;
    float busVoltage = 0;
    float phaseCurrent = 0;
    float phaseVoltage = 0;
    quint8 end = 0;
    // size = 8 + 8 + 16 + 32 * 5 + 8
}msgData;

#endif // SERIAL_H
