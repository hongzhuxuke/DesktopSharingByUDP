#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBuffer>
#include <QDesktopWidget>
#include <QPixmap>
#include <QScreen>
#include "ConfigSetting.h"
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>
#define  CONFIG_FILE "config.ini"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint /*| Qt::WindowStaysOnTopHint*/);
    setAttribute(Qt::WA_TranslucentBackground, true);
    ui->setupUi(this);
    ui->lineEdit->hide();
    ui->label->hide();
    //setFixedSize(10,10);
    m_receiver=new QUdpSocket(this);
        //绑定发送端，ShareAddress允许多接收端绑定6666端口
        m_receiver->bind(6666,QUdpSocket::ShareAddress);
        //当接收端接收到数据时，就会发送readRead信号
        connect(m_receiver,&QUdpSocket::readyRead,this,&MainWindow::processData);
		slot_capther();
    connect(&mT, &QTimer::timeout, this, &MainWindow::slot_capther);
    startCapther();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startCapther()
{
    QString strDir = ConfigFilePath();
    qDebug()<< __LINE__ << strDir << endl;
    int time = ConfigSetting::ReadInt(strDir, GROUP_DEFAULT, CAPTHER_TIME, 30);
    qDebug()<< __LINE__ << time << endl;
    mT.start(time*1000);
}

QString MainWindow::ConfigFilePath()
{
    QString strDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir dir(strDir);
    strDir = dir.absoluteFilePath(CONFIG_FILE);
	strDir = QString("./%1").arg( CONFIG_FILE);

    return strDir;
}


void MainWindow::processData()
{
    QString strData;
    //有未处理的数据报
    while(m_receiver->hasPendingDatagrams()){
        QByteArray dataGram;
        //读取的数据报大小
        dataGram.resize(m_receiver->pendingDatagramSize());

        QHostAddress Sendhost;
        quint16 Sendport;
        m_receiver->readDatagram(dataGram.data(),dataGram.size(),&Sendhost, &Sendport);
        qDebug() << __LINE__ << "xk22 m_receiver" << dataGram << endl;
        if(QString(dataGram).contains("Broadcast xuke1989"))
        {
            ui->lineEdit->setText(dataGram + " " +Sendhost.toString()+":"+ Sendport);   //将接收到的数据显示到标签上
            mSendhost = Sendhost;
            mSendport = Sendport;


            QByteArray dataRequst=QString("Received xuke1989").toUtf8();//响应广播
            m_receiver->writeDatagram(dataRequst.data(),
                                    dataRequst.size(),
                                    mSendhost,    //udp广播地址
                                    7777);
        }
        else if(QString(dataGram).contains("NewDesktop xuke1989"))
        {

            if(!thread.isRunning())
            {
                 QStringList list = QString(dataGram).split(" ");
                //截取桌面
                qDebug()<< __LINE__ << "xk22 "  << "S52" << endl;
                QScreen* dss = QGuiApplication::primaryScreen();
                QPixmap screen= dss->grabWindow(QApplication::desktop()->winId(), 0, 0, -1, -1);
                 screen = screen.scaled(1920, 1080, Qt::KeepAspectRatio,Qt::SmoothTransformation);
                 //320 ， 180
                newpixmap = screen;
                if(oldpixmap.toImage()!=newpixmap.toImage())
                {
                    oldpixmap = newpixmap;
                    thread.startThread(mSendhost, 7777, newpixmap, list[2].toInt());
                }
            }
        }
    }
}

void MainWindow::slot_capther()
{
    //static int index = 0;

    QScreen* dss = QGuiApplication::primaryScreen();
    QPixmap screen= dss->grabWindow(QApplication::desktop()->winId(), 0, 0, -1, -1);
     //screen = screen.scaled(1920, 1080, Qt::KeepAspectRatio,Qt::SmoothTransformation);
     //320 ， 180
     QString strDir = ConfigFilePath();
     QString strOut = ConfigSetting::ReadString(strDir, GROUP_DEFAULT, PATH_OUT, "");
        qDebug()<< __LINE__ << QString("%1/%2.png").arg(strOut).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")/*index++*/) << endl;
    QString str = QString("%1/%2.png").arg(strOut).arg(QDateTime::currentDateTime().toString("hhmmss"));
		screen.save(str);
}

