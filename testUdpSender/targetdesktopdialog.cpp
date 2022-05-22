#include "targetdesktopdialog.h"
#include "ui_targetdesktopdialog.h"
#include <QDebug>

targetDesktopDialog::targetDesktopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::targetDesktopDialog)
{
    //setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint /*| Qt::WindowStaysOnTopHint*/);

    ui->setupUi(this);
    l[0] = ui->l1;
    l[1] = ui->l2;
    l[2] = ui->l3;
    l[3] = ui->l4;
    l[4] = ui->l5;
    l[5] = ui->l6;
    l[6] = ui->l7;
    l[7] = ui->l8;
    l[8] = ui->l9;
    l[9] = ui->l10;
    l[10] = ui->l11;
    l[11] = ui->l12;
    l[12] = ui->l13;
    l[13] = ui->l14;
    l[14] = ui->l15;
    l[15] = ui->l16;
    l[16] = ui->l17;
    l[17] = ui->l18;
    l[18] = ui->l19;
    l[19] = ui->l20;
    l[20] = ui->l21;
    l[21] = ui->l22;
    l[22] = ui->l23;
    l[23] = ui->l24;
    l[24] = ui->l25;
    l[25] = ui->l26;
    l[26] = ui->l27;
    l[27] = ui->l28;
    l[28] = ui->l29;
    l[29] = ui->l30;
    l[30] = ui->l31;
    l[31] = ui->l32;
    l[32] = ui->l33;
    l[33] = ui->l34;
    l[34] = ui->l35;
    l[35] = ui->l36;

}

targetDesktopDialog::~targetDesktopDialog()
{
    delete ui;
}

void targetDesktopDialog::slot_receiveNew(QByteArray dataGram, int index)
{
    //static int index = 0;
    qDebug()<< __LINE__<< "xk22 " << index << dataGram.size() << " targetDesktopDialog::slot_receiveNew" << endl;
//    QByteArray Num = dataGram.mid(0,sizeof(int));
//    int iNum = Num.toInt();
//    QByteArray tempData = dataGram.mid(1+sizeof(int));
    QImage image;
    image.loadFromData(dataGram);

    l[index]->setPixmap(QPixmap::fromImage(image).scaled(l[index]->size()));

    image.save(QString("%1.png").arg(index++));
}

void targetDesktopDialog::on_btnNew_clicked()
{
    qDebug()<< "xk22 "  << "targetDesktopDialog::on_btnNew_clicked()" << endl;
    emit sig_New();
}

void targetDesktopDialog::on_btnPre_clicked()
{

}

void targetDesktopDialog::on_btnNext_clicked()
{

}

bool targetDesktopDialog::slot_CloseClicked()
{
    close();
    return false;
}

void targetDesktopDialog::slot_MinClicked()
{
    showMinimized();
}

void targetDesktopDialog::slot_MaxClicked()
{
    showMaximized();
}
