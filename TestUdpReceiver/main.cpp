#include "mainwindow.h"
#include <QSharedMemory> 
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QSharedMemory singleton(a.applicationName());
	if (!singleton.create(1))
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("��ܰ��ʾ"), QString::fromLocal8Bit("�����Ѿ����У�"));
		return false;
	}


    MainWindow w;
    //w.setHidden(true);
    w.showMaximized();

    //w.move(-200,-200);
    return a.exec();
}
