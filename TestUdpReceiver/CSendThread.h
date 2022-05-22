#ifndef H_CEPUBCREATORTHREAD_H
#define H_CEPUBCREATORTHREAD_H

#include <QThread> 

#include <QFileInfo> 
#include <QVector> 
#include <QUdpSocket>
#include <QHostAddress>
#include <QPixmap>

class CSendThread :
	public QThread
{
	Q_OBJECT
public:
    CSendThread();
    ~CSendThread();
    void startThread(QHostAddress mSendhost, quint16 mSendport, QPixmap pixmap, int index);
	void setMesUI(QObject* pobj);
	void run() override;


signals:

	
private:

    QHostAddress mSendhost;
    quint16 mSendport;
    QUdpSocket* m_receiver; //udpΩ” ‹∂À
    QPixmap newpixmap;
    int index;
};

#endif // ! H_CEPUBCREATORTHREAD_H
