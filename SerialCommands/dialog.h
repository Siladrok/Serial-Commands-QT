#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void on_serialPortBox_currentIndexChanged(int index);

    void on_connectButton_clicked();

    void on_closeButton_clicked();

    void on_commandButton_clicked();

    void on_commandLine_textChanged(const QString &arg1);

    void on_commandLine_returnPressed();

    void on_baudRateBox_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    QSerialPort *MySerialDevice;
    QString my_device_port_name;
    QString my_baud_rate;
    QString command;
};
#endif // DIALOG_H
