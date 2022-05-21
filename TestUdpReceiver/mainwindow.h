#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void processData();
private:
    Ui::MainWindow *ui;
    QUdpSocket* m_receiver; //udp接受端
    QHostAddress mSendhost;
    quint16 mSendport;
    QPixmap newpixmap;
    QPixmap oldpixmap;
};
#endif // MAINWINDOW_H
