#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //bool my_device_available = false;
    QString my_device_port_name ="";
    QString my_baud_rate ="";
    QString status="";
    QString command ="";

    MySerialDevice = new QSerialPort(this);

    //By default set the first port @ 9600BaudRate
    my_device_port_name = QSerialPortInfo::availablePorts().at(0).portName();
    my_baud_rate ="9600";
    MySerialDevice->setBaudRate(QSerialPort::Baud9600);


    //Populate the BaudRate combobox
    ui->baudRateBox->addItem("9600");
    ui->baudRateBox->addItem("19200");
    ui->baudRateBox->addItem("38400");
    ui->baudRateBox->addItem("57600");
    ui->baudRateBox->addItem("115200");

    //Showing Number of Ports
    int num_of_ports = QSerialPortInfo::availablePorts().length();
    ui->available_ports_label->setText(QString::number(num_of_ports));
    //qDebug() <<"Number of Availiable ports: " <<QSerialPortInfo::availablePorts().length();


    //Populate the SerialPortBox
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        ui->serialPortBox->addItem(serialPortInfo.portName());
    }

    //Configure basic options for the serial
    MySerialDevice->setDataBits(QSerialPort::Data8);
    MySerialDevice->setFlowControl(QSerialPort::NoFlowControl);
    MySerialDevice->setParity(QSerialPort::NoParity);
    MySerialDevice->setStopBits(QSerialPort::OneStop);


}

Dialog::~Dialog()
{
    if(MySerialDevice->isOpen()){
        MySerialDevice->close();
    }
    delete ui;
}


void Dialog::on_serialPortBox_currentIndexChanged(int index)
{
        my_device_port_name = QSerialPortInfo::availablePorts().at(index).portName();
        MySerialDevice->setPortName(my_device_port_name);
        ui->descriptionLabel->setText(QSerialPortInfo::availablePorts().at(index).description());
        ui->manufacturerLabel->setText(QSerialPortInfo::availablePorts().at(index).manufacturer());
        qDebug()<<my_device_port_name;
}

void Dialog::on_connectButton_clicked()
{
        MySerialDevice->open(QIODevice::WriteOnly);
        //Display Status Label
        ui->statusLabel->setText(my_device_port_name +" @ "+ my_baud_rate);
        ui->on_off_label->setText("Connected");
        ui->on_off_label->setStyleSheet("QLabel {font-weight: bold; color : green; }");
}

void Dialog::on_closeButton_clicked()
{
    if(MySerialDevice->isOpen()){
        MySerialDevice->close();
    }
    ui->on_off_label->setText("Disconnected");
    ui->on_off_label->setStyleSheet("QLabel {font-weight: bold; color : red; }");
}

void Dialog::on_commandButton_clicked()
{
        MySerialDevice->write(command.toStdString().c_str());
        MySerialDevice->waitForBytesWritten(100);
        qDebug()<<command.toStdString().c_str();
}

void Dialog::on_commandLine_textChanged(const QString &arg1)
{
        command = arg1;
        qDebug()<<command;
}

void Dialog::on_commandLine_returnPressed()
{
    MySerialDevice->write(command.toStdString().c_str());
    MySerialDevice->waitForBytesWritten(100);
    qDebug()<<command.toStdString().c_str();
}

void Dialog::on_baudRateBox_currentIndexChanged(int index)
{
    if(index==0){
    MySerialDevice->setBaudRate(QSerialPort::Baud9600);
    my_baud_rate ="9600";

    }
    else if(index==1){
    MySerialDevice->setBaudRate(QSerialPort::Baud19200);
    my_baud_rate ="19200";
    }
    else if(index==2){
    MySerialDevice->setBaudRate(QSerialPort::Baud38400);
    my_baud_rate ="38400";
    }
    else if(index==3){
    MySerialDevice->setBaudRate(QSerialPort::Baud57600);
    my_baud_rate="57600";
    }
    else{
    MySerialDevice->setBaudRate(QSerialPort::Baud115200);
    my_baud_rate ="115200";
    }
}
