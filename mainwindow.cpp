#include <QDir>
#include <QMessageBox>
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
    connect(ui->comboBox_car, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxCarChanged(int)));
    connect(ui->dial, &QDial::valueChanged, this, &MainWindow::onDailChanged);

    QDir dir("C:/config");
    QStringList files = dir.entryList(QDir::Files); // 获取文件夹内所有文件
    ui->comboBox_car->addItems(files);
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

void MainWindow::onComboBoxCarChanged(int index) {
    // 获取当前选中的文件名
    QString selectedFile = ui->comboBox_car->currentText();
    // 构建完整的文件路径
    QString filePath = "C:/config/" + selectedFile;

    // 打开文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "读取文件", "无法打开文件：" + filePath);
        return;
    }

    // 读取文件内容
    QTextStream in(&file);
    QString fileContent = in.readLine();
    file.close();

    // 处理文件内容，例如显示在文本框中
    QStringList parts = fileContent.split(" "); // 使用空格分割字符串

    if (parts.size() == 2) { // 确保分割后有两部分
        bool ok1, ok2;
        min = parts.at(0).toInt(&ok1); // 将第一个字符串转换为整数
        max = parts.at(1).toInt(&ok2); // 将第二个字符串转换为整数
        if (ok1 && ok2) { // 确保两个字符串都成功转换为整数
            ;
        } else {
            // 转换失败的处理
            qDebug() << "转换失败";
        }
    } else {
        // 分割结果不是两部分的处理
        qDebug() << "格式错误";
    }
}

void MainWindow::onDailChanged(int value)
{
    ui->lcdNumber_youMen->display(value);
}
