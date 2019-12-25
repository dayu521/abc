#include "myscreen.h"
#include<QPainter>
#include<QPixmap>
#include<QtDebug>
#include"simulator.h"

MyScreen::MyScreen(QWidget *parent) : QWidget(parent)
{
}

void MyScreen::setSource(Simulator *x_)
{
    if(pix!=x_->getPixmap()){
        pix=x_->getPixmap();
        resize(pix->size());
    }
}

void MyScreen::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,*pix);
}

