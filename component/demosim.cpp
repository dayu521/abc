#include "demosim.h"
#include<QPixmap>
#include<QWidget>
#include<QPainter>

DemoSim::DemoSim(QString name_):Simulator(&elementProperties),name(name_)
{

    panel=new QWidget;
    panel->setAutoFillBackground(true);
    auto pp=panel->palette();
    pp.setColor(QPalette::Background,Qt::red);
    panel->resize(800,500);
    panel->setPalette(pp);
    k=10;
}

DemoSim::~DemoSim()
{
}

QWidget *DemoSim::getUi()
{
    return panel;
}

QString DemoSim::getName() const
{
    return name;
}

void DemoSim::produceSimulateData()
{

}

void DemoSim::clearSimulateData()
{
    pix->fill(Qt::white);
}

void DemoSim::setPixmap(QPixmap * p_)
{
    pix=p_;
}

void DemoSim::currentSnapshot(int n_) const
{
//    pix[currentPixIndex]->fill(Qt::white);
//    QPainter p_(pix[currentPixIndex]);
//    p_.setBrush(Qt::red);
//    auto r_=elementProperties[0];
//    for(int i=0;i<k;i++){
//        p_.drawEllipse(elementProperties[0],elementProperties[0],r_,r_);
//        p_.translate(r_,0);
//    }
    n_--;
    pix->fill(Qt::white);
    QPainter p_(pix);
    p_.setBrush(Qt::red);
    int y=n_/10;
    int x=n_-y*10;
    for(int i=0;i<y;i++)
        for(int j=0;j<10;j++)
            p_.drawRect(j*elementProperties[0],i*elementProperties[0],elementProperties[0],elementProperties[0]);
    for(int i=0;i<=x;i++)
        p_.drawRect(i*elementProperties[0],y*elementProperties[0],elementProperties[0],elementProperties[0]);
}

//此函数有待重构
QSize DemoSim::calculationMinPixSize()
{
    int w_=elementProperties[1]+elementProperties[0]*k;
    int h_=elementProperties[1]+elementProperties[2]*(k-1);
    return {w_,h_};
}

void DemoSim::nextFrame(int n_)
{
    if(n_==0)
        pix->fill();
    QPainter p_(pix);
    p_.setBrush(Qt::red);
    int y=n_/10;
    int x=n_-y*10;
    p_.drawRect(x*elementProperties[0],y*elementProperties[0],elementProperties[0],elementProperties[0]);
}

int DemoSim::frameAllNumber() const
{
    return 100;
}

void DemoSim::setPixmapsize()
{

}
