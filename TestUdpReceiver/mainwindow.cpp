#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBuffer>
#include <QDesktopWidget>
#include <QPixmap>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_receiver=new QUdpSocket(this);
        //绑定发送端，ShareAddress允许多接收端绑定6666端口
        m_receiver->bind(6666,QUdpSocket::ShareAddress);
        //当接收端接收到数据时，就会发送readRead信号
        connect(m_receiver,&QUdpSocket::readyRead,this,&MainWindow::processData);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        {//截取桌面
            qDebug()<< __LINE__ << "xk22 "  << "S52" << endl;
            QScreen* dss = QGuiApplication::primaryScreen();
            QPixmap screen= dss->grabWindow(QApplication::desktop()->winId(), 0, 0, -1, -1);

//            QDesktopWidget* desktop = QApplication::desktop();
//            QPixmap screen = QPixmap::grabWindow(desktop->winId());
//            QScreen *primaryScreen = qApp.primaryScreen();
//            QPixmap screen = primaryScreen->grabWindow(0);
            //QScreen* screen = QGuiApplication::primaryScreen();
            //QPixmap::grabWidget(desktop->winId());
            /*QPixmap screen = screen.scaled(320, 192, Qt::KeepAspectRatio,Qt::SmoothTransformation);
            */
            newpixmap = screen;
            if(oldpixmap.toImage()!=newpixmap.toImage())
            {
                oldpixmap = newpixmap;


                QImage image;
                QPixmap temp = newpixmap.copy(0, 0, 320, 192);
                image = temp.toImage();
                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::ReadWrite);
                image.save(&buffer, "PNG");

                qDebug()<< __LINE__<< "xk22 image "  << QString(ba)<< endl;
                //ba = QString("XXXXXXXX").toUtf8();
                //ba = ba.toBase64();
                m_receiver->writeDatagram(ba.data(),
                                        ba.size(),
                                        QHostAddress::Broadcast/*mSendhost*/,    //udp广播地址
                                        7777);
            }
        }
    }
}
