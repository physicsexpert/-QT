#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    serialPort = new QSerialPort(this);//实例化


    //扫描串口，并添加
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(info.portName());

    }

    // 读取数据
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));






}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked(bool checked)
{
     if (checked) {
    // 设置要打开的串口的名字
            serialPort->setPortName(ui->comboBox->currentText());

            // 设置波特率
            serialPort->setBaudRate(ui->comboBox_2->currentText().toInt());

            // 设置停止位
            serialPort->setStopBits(QSerialPort::StopBits(ui->comboBox_3->currentText().toInt()));

            // 设置数据位
            serialPort->setDataBits(QSerialPort::DataBits(ui->comboBox_4->currentText().toInt()));
            // 设置校验位
                   switch (ui->comboBox_5->currentIndex()) {
                   case 0:
                       serialPort->setParity(QSerialPort::NoParity);
                       break;
                   case 1:
                       serialPort->setParity(QSerialPort::EvenParity);
                       break;
                   case 2:
                       serialPort->setParity(QSerialPort::OddParity);
                       break;
                   case 3:
                       serialPort->setParity(QSerialPort::SpaceParity);
                       break;
                   case 4:
                       serialPort->setParity(QSerialPort::MarkParity);
                       break;
                   default:
                       break;
}
                   // 设置流控为无
                   serialPort->setFlowControl(QSerialPort::NoFlowControl);

                   if (!serialPort->open(QIODevice::ReadWrite)) {

                       QMessageBox message(QMessageBox::NoIcon, "串口打开失败", "你干嘛~~哎呦~~油饼食不食！鸽鸽下蛋不给你吃");
                       message.setIconPixmap(QPixmap("aa.jpg"));
                       message.exec();
                       return;
                   }

                   ui->comboBox->setEnabled(false);
                   ui->comboBox_2->setEnabled(false);
                   ui->comboBox_3->setEnabled(false);
                   ui->comboBox_4->setEnabled(false);
                   ui->comboBox_5->setEnabled(false);

                   ui->pushButton->setText("关闭串口");
                   ui->label_10->setText("串口已打开");
               } else {
                   // 关闭串口
                   serialPort->close();
                   ui->comboBox->setEnabled(true);
                   ui->comboBox_2->setEnabled(true);
                   ui->comboBox_3->setEnabled(true);
                   ui->comboBox_4->setEnabled(true);
                   ui->comboBox_5->setEnabled(true);
                   ui->pushButton->setText("打开串口");
                   ui->label_10->setText("串口已关闭");
               }

}

void Widget::readData()
{
    // 接收数据
       ui->textBrowser->insertPlainText(serialPort->readAll());
}




void Widget::on_pushButton_2_clicked()
{
    // 发送数据
    serialPort->write(ui->textEdit->toPlainText().toUtf8());
    ui->label_10->setText("数据已发送");
}

void Widget::on_pushButton_3_clicked()
{
    // 清空发送的数据
    ui->textEdit->clear();
    ui->label_10->setText("数据已清除");
}
