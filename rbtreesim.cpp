#include "rbtreesim.h"
#include<QPixmap>
#include<QWidget>
#include<QPainter>

RBtreeSim::RBtreeSim(QString name_):Simulator(&elementProperties),name(name_)
{
    for(int i=0;i<pixCount;i++)
        pix[i]=new QPixmap(pixSize[i],pixSize[i]);
    panel=new QWidget;
    panel->setAutoFillBackground(true);
    auto pp=panel->palette();
    pp.setColor(QPalette::Background,Qt::red);
    panel->resize(800,500);
    panel->setPalette(pp);
    elementProperties.append(20);
    elementProperties.append(40);
    elementProperties.append(20*3/2);
    elementProperties.append(16);
    k=10;
}

RBtreeSim::~RBtreeSim()
{
    for(int i=0;i<pixCount;i++)
        delete pix[i];
}

QWidget *RBtreeSim::getUi()
{
    return panel;
}

QString RBtreeSim::getName() const
{
    return name;
}

void RBtreeSim::startSimulate()
{

}

void RBtreeSim::clearSimulate()
{

}

QPixmap *RBtreeSim::getPixmap() const
{
    return pix[currentPixIndex];
}

void RBtreeSim::setPmpSize() const
{

}

void RBtreeSim::currentSnapshot() const
{
    pix[currentPixIndex]->fill(Qt::white);
    QPainter p_(pix[currentPixIndex]);
    p_.setBrush(Qt::red);
    auto r_=elementProperties[0];
    for(int i=0;i<k;i++){
        p_.drawEllipse(elementProperties[0],elementProperties[0],r_,r_);
        p_.translate(r_,0);
    }
}

//此函数有待重构
QSize RBtreeSim::calculationPixSize()
{
    int w_=elementProperties[1]+elementProperties[0]*k;
    int h_=elementProperties[1]+elementProperties[2]*(k-1);
    auto max_=w_>h_?w_:h_;
    currentPixIndex=0;
    while(max_>pixSize[currentPixIndex])
        currentPixIndex++;
    return {w_,h_};
}

void RBtreeSim::nextFrame() const
{
   QPainter p_(pix[currentPixIndex]);
   p_.setBrush(Qt::red);
   auto r_=elementProperties[0];
   for(int i=0;i<k;i++){
       p_.drawEllipse(elementProperties[0],elementProperties[0],r_,r_);
       p_.translate(r_,0);
   }
}

void RBtreeSim::setPixmapsize()
{

}
