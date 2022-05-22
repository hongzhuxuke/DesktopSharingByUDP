#include "CSendThread.h"

//#include <QDir>
//#include <QStringList>

//#include <QString>
//#include <QDateTime>
#include <QDebug>
//#include <QThreadPool>
//#include <QPixmap>
//#include <QGuiApplication>
#include <iostream>
#include <fstream>
#include <time.h>
#include <QBuffer>

//#include <QApplication>
//#include <QDesktopWidget>

using namespace std;

void add_log(const char *logfile, const char *fmt, ...)
{

	int fd;
	va_list ap;
	char msg[1024];
	struct tm *nowp, now;
	ofstream ofs;  //提供写文件的功能
	time_t t = time(0);
	char tmp[64];
	memset(tmp, 0, 64);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X ", localtime(&t));

	char tmpFile[100];
	memset(tmpFile, 0, 100);
	strftime(tmpFile, sizeof(tmpFile), "%Y%m%d", localtime(&t));
	strcat(tmpFile, logfile);
	strcat(tmpFile, ".log");
	ofs.open(tmpFile, ios::app);

	ofs << tmp;

	memset(msg, 0, sizeof(msg));
	va_start(ap, fmt);
	vsnprintf(msg, sizeof(msg), fmt, ap);
	va_end(ap);
	ofs << msg << "        \n";


	ofs.close();
}


CSendThread::CSendThread()
{
    m_receiver=new QUdpSocket(this);
}

CSendThread::~CSendThread()
{

}

void CSendThread::startThread(QHostAddress Sendhost, quint16 Sendport,  QPixmap pixmap, int Tindex)
{
    mSendhost = Sendhost;
    mSendport  = Sendport;
    newpixmap = pixmap;
    index = Tindex;
    this->start();
}


void CSendThread::setMesUI(QObject* pobj)
{
    //mpobj = pobj;
}

void CSendThread::run()
{

        QImage image;
        QPixmap temp;
        //int index = 0;
        int j = index/6;
        int i = index%6;
        qDebug()<< __LINE__ << " III " << QString("index:%1 i:%2 j:%3").arg(index).arg(i).arg(j)<< endl;
//        for(int i = 3; i< 6; i++)
//        {
//            for(int j = 0; j<6; i++)
//            {
                temp = newpixmap.copy(320*i, 180*j, 320, 180);
                image = temp.toImage();
                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::ReadWrite);
                image.save(&buffer, "PNG");

//                char* buff = new char[sizeof(int)+ba.size() + 1];
//                memset(buff, 0, sizeof(int)+ba.size() + 1);
//                qDebug()<< __LINE__ << "xk22 len "  << ba.size() << "index:" << index << endl;
//                char* tempC = buff;
//                memcpy(tempC, &index, sizeof(int));
//                tempC+=sizeof(int);
//                memcpy(tempC,ba.data(), ba.size());
//                qDebug()<< __LINE__<< "xk22 image "  << QString(ba)<< endl;
                m_receiver->writeDatagram(/*buff*/ba.data(),
                                        ba.size()/*+sizeof(int)*/,
                                        /*QHostAddress::Broadcast*/mSendhost,    //udp广播地址
                                        7777);
                //delete buff;
                //QThread::sleep(20);
                return;
            //}
        //}


}
