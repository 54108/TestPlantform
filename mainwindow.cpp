#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLCDNumber* lspeed = ui->lcdNumber_zhuansu;
    lspeed->setDigitCount(15);

    SerialThread *serialThread = new SerialThread();

    QSerialPort *sp =new QSerialPort(this);

    QList<QSerialPortInfo> serialPortList=QSerialPortInfo::availablePorts();

    //如果没有可用串口，则在状态栏提示相应信息
    if(serialPortList.isEmpty()){
        this->statusBar()->showMessage("没有可用串口，请插入串口或重启电脑重试");
    }else {
        //有可用串口的情况下，把串口遍历显示到下拉框中
        this->statusBar()->showMessage("可用串口数量为:"+QString::number( serialPortList.count()) );

        //创建遍历迭代器，把串口遍历显示到下拉框中
        QList<QSerialPortInfo>::Iterator nextSerialPort=serialPortList.begin();
        while (nextSerialPort != serialPortList.end()) {
            ui->comboBox->addItem(nextSerialPort->portName());
            nextSerialPort++;
        }
    }

    serialThread->init(sp);

    connect(serialThread, &SerialThread::readydata, this, &MainWindow::updatespeed);
    serialThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatespeed(const QByteArray &data)
{
    QLCDNumber* lspeed = ui->lcdNumber;
    lspeed->display(data);
}
