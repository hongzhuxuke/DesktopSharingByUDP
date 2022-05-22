#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtNetwork>
#include <QtWidgets>
#include "targetdesktopdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     m_sender=new QUdpSocket(this);
     m_sender->bind(7777,QUdpSocket::ShareAddress);
     //当接收端接收到数据时，就会发送readRead信号
     connect(m_sender,&QUdpSocket::readyRead,this,&MainWindow::processData);

     mpDlg  = new targetDesktopDialog(this);
     connect(mpDlg, &targetDesktopDialog::sig_New, this, &MainWindow::slot_GetNew);
     connect( this, &MainWindow::sig_receiveNew,mpDlg, &targetDesktopDialog::slot_receiveNew);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_clicked()
{
    ui->ledtMgs->setText(getHost());
    QByteArray dataGram=ui->ledtMgs->text().toUtf8();
        m_sender->writeDatagram(dataGram.data(),
                                dataGram.size(),
                                QHostAddress::Broadcast,    //udp广播地址
                                6666);
}

QString MainWindow::getHost()
{
    QString strRef(QHostInfo::localHostName());
    strRef.append(" ");
    qDebug()<< __LINE__<< "xkk " << strRef<< endl;
        const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

        for (const QHostAddress &ipAddress : ipAddressesList) {
            if (!ipAddress.isLoopback()
                    && ipAddress.protocol() == QAbstractSocket::IPv4Protocol
                    && ipAddress != QHostAddress(QHostAddress::LocalHost))
            {
                strRef.append(ipAddress.toString());
                //ui->addressSelector->addItem(ipAddress.toString());
                qDebug()<< __LINE__<< "xkk " << strRef<< endl;
            }
        }

        strRef.append(" ");
        strRef.append("Broadcast xuke1989");//广播命令 NewDesktop xuke1989
        return strRef;
}



void MainWindow::processData()
{
    QString strData;
    //有未处理的数据报
    while(m_sender->hasPendingDatagrams()){
        QByteArray dataGram;
        //读取的数据报大小
        dataGram.resize(m_sender->pendingDatagramSize());
        qDebug()<< __LINE__<< "xk22 "  << "72 Sender receive Image" << endl;
        QHostAddress Sendhost;
        quint16 Sendport;
        m_sender->readDatagram(dataGram.data(),dataGram.size(),&Sendhost, &Sendport);
        qDebug()<< __LINE__<< "xk22 76" << Sendhost.toString() << ":"<<  Sendport << QString(dataGram) << endl;
        if(QString(dataGram).contains("Received xuke1989"))
        {
            mSendhost = Sendhost;
            mSendport = Sendport;
            ui->lineEdit->setText(dataGram + " " +mSendhost.toString()+":"+ mSendport);   //将接收到的数据显示到标签上

            mpDlg->show();
        }
        else
        {
            qDebug()<< __LINE__<< "xk22 "  << "Sender receive Image" << endl;
            emit sig_receiveNew(dataGram, index);
            index++;
            getNewDestop();
        }
    }
}

void MainWindow::slot_GetNew()
{
    index = 0;
    getNewDestop();
    //on_btn_clicked();
}

void MainWindow::getNewDestop()
{
    if(index<=35)
    {
        QByteArray dataRequst=QString("NewDesktop xuke1989 %1").arg(index).toUtf8(); //获取新页面

        qDebug()<< __LINE__<< "xk22 " << mSendhost.toString()  << " Sender MainWindow::slot_GetNew()" << endl;
        m_sender->writeDatagram(dataRequst.data(),
                                dataRequst.size(),
                                /*QHostAddress::Broadcast*/mSendhost,    //udp广播地址
                                6666);
    }
    else{index = 0;}

}
