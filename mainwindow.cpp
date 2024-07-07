#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SerialThread *serialThread = new SerialThread();
    QSerialPort *sp =new QSerialPort(this);
    QList<QSerialPortInfo> serialPortList=QSerialPortInfo::availablePorts();

    if(serialPortList.isEmpty()){
        this->statusBar()->showMessage("没有可用串口，请插入串口或重启电脑重试");
    }else {
        this->statusBar()->showMessage("可用串口数量为:"+QString::number( serialPortList.count()));
        QList<QSerialPortInfo>::Iterator nextSerialPort=serialPortList.begin();
        while (nextSerialPort != serialPortList.end()) {
            ui->comboBox->addItem(nextSerialPort->portName());
            nextSerialPort++;
        }
    }
    serialThread->init(sp);
    serialThread->start();

    connect(serialThread, &SerialThread::readydata, this, &MainWindow::updatelcdnumber);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatelcdnumber(const QByteArray &data)
{
    QLCDNumber* lspeed = ui->lcdNumber_zhuanSu;
    QLCDNumber* lwheelSpeed = ui->lcdNumber_lunZhuanSu;
    QLCDNumber* laxisTorque = ui->lcdNumber_zhouNiuJv;
    QLCDNumber* lacceleration = ui->lcdNumber_jiaSuDu;
    QLCDNumber* lbusCurrent = ui->lcdNumber_muDianLiu;
    QLCDNumber* lphaseCurrent = ui->lcdNumber_xiangDianLiu;
    QLCDNumber* lvoltage = ui->lcdNumber_dianYa;
    QLCDNumber* lpower = ui->lcdNumber_gongLv;
    QLCDNumber* lefficiency = ui->lcdNumber_xiaoLv;

    int speed;
    float wheelSpeed,axisTorque,acceleration,busCurrent,phaseCurrent,voltage,power,efficiency;

    wheelSpeed = speed * 123;
    acceleration = axisTorque * 123 / 456;
    power = phaseCurrent * voltage;
    efficiency = power / busCurrent / 380;


    lspeed->display(data);
    lwheelSpeed->display(data);
}
