#include "targetdesktopdialog.h"
#include "ui_targetdesktopdialog.h"
#include <QDebug>

targetDesktopDialog::targetDesktopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::targetDesktopDialog)
{
    ui->setupUi(this);
}

targetDesktopDialog::~targetDesktopDialog()
{
    delete ui;
}

void targetDesktopDialog::slot_receiveNew(QByteArray dataGram)
{
    static int index = 0;
    qDebug()<< __LINE__<< "xk22 " << index << " targetDesktopDialog::slot_receiveNew" << endl;

    QImage image;
    image.loadFromData(dataGram);

    ui->label->setPixmap(QPixmap::fromImage(image).scaled(ui->label->size()));

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
