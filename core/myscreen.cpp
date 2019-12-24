#include "myscreen.h"
#include<QPainter>
#include<QPixmap>
#include<QtDebug>

MyScreen::MyScreen(QWidget *parent) : QWidget(parent)
{
//    setAutoFillBackground(true);
}

void MyScreen::paint(QPixmap && x_)
{
//    QPainter p_(&pix);
//    p_.drawPixmap(0,0,x_);
    pix=x_;
    update();
}

void MyScreen::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,pix);
}

void MyScreen::resizeEvent(QResizeEvent *event)
{

}
