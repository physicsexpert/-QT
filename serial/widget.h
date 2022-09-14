#ifndef WIDGET_H
#define WIDGET_H
#include <QSerialPort> //串口类
#include <QSerialPortInfo>//串口信息类
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::Widget *ui;
    QSerialPort *serialPort;

private slots:
    void readData();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();


};
#endif // WIDGET_H
