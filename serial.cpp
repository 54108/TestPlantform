#include "serial.h"
#include "mainwindow.h"

SerialThread::SerialThread(QObject *parent) : QThread(parent){};

void SerialThread::init(QSerialPort * sp)
{
    // 配置串口参数
    serial = sp;
    serial->setPortName("com3");
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
}

SerialThread::~SerialThread()
{
    // 关闭串口
    serial->close();
    // 清理资源
    delete serial;
}

void SerialThread::run() {
    if (serial->isOpen()) {
        // 串口打开成功
        while (serial->isOpen()) {
            // 读取数据
            if (serial->canReadLine()) {
                data = serial->readLine();
                emit readydata(data);
            }
            QThread::msleep(50);
        }
    } else {
        qFatal("无法打开串口！");
    }
}
