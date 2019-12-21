#include "myscreen.h"
#include<QPainter>
#include<QPixmap>
#include<QtDebug>

MyScreen::MyScreen(QWidget *parent) : QWidget(parent)
{
//    setAutoFillBackground(true);
}

void MyScreen::paint(int x_)
{
    pix.fill(Qt::white);
    QPainter p_(&pix);
    p_.drawText(0,50,QString::number(x_));
//    update();
    qDebug()<<x_;
}

void MyScreen::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,pix);
}
