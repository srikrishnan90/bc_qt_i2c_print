#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(temp()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Pi2c arduino(7);
    QString data=ui->lineEdit->text();
    char* ch;
    QByteArray ba=data.toLatin1();
    ch=ba.data();
    QThread::msleep(100);
    arduino.i2cWrite(ch,30);
    QThread::msleep(100);
}

void MainWindow::temp()
{
    Pi2c arduino(7); //Create a new object "arduino" using address "0x07"
    char receive[30]; //Create a buffer of char (single bytes) for the data
    //Receive from the Arduino and put the contents into the "receive" char array
    //timer1->stop();
    QThread::msleep(100);
    arduino.i2cRead(receive,30);
    QThread::msleep(100);
    QString str=receive;
    //Print out what the Arduino is sending...
    //qDebug() << "Arduino Says: " << str.mid(0,2);
    ui->lineEdit_2->setText(str.mid(0,4));
    ui->lineEdit_3->setText(str.mid(5,9));

}
