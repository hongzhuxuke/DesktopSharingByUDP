#ifndef TARGETDESKTOPDIALOG_H
#define TARGETDESKTOPDIALOG_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class targetDesktopDialog;
}

class targetDesktopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit targetDesktopDialog(QWidget *parent = nullptr);
    ~targetDesktopDialog();
signals:
    void sig_New();
public slots:
    void slot_receiveNew(QByteArray dataGram, int index);
private slots:

private slots:
    void on_btnNew_clicked();   //按钮点击信号

    void on_btnPre_clicked();
    void on_btnNext_clicked();


private:
    Ui::targetDesktopDialog *ui;
    QLabel* l[36];
};

#endif // TARGETDESKTOPDIALOG_H
