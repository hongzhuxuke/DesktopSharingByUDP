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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("温馨提示"), QString::fromLocal8Bit("工具已经运行！"));
		return false;
	}


    MainWindow w;
    //w.setHidden(true);
    w.showMaximized();

    //w.move(-200,-200);
    return a.exec();
}
