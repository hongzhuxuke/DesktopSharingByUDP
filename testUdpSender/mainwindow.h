#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class targetDesktopDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sig_receiveNew(QByteArray dataGram);
private slots:
    void on_btn_clicked();   //按钮点击信号
    void processData();
    void slot_GetNew();

private:
    QString getHost();

    Ui::MainWindow *ui;
    QUdpSocket* m_sender;   //udp发送端
    QHostAddress mSendhost;
    quint16 mSendport;
    targetDesktopDialog* mpDlg = nullptr;
};
#endif // MAINWINDOW_H
