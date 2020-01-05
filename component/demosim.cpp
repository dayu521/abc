#include "demosim.h"
#include<QPixmap>
#include<QWidget>
#include<QPainter>

DemoSim::DemoSim(QString name_):name(name_)
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

}

void DemoSim::setPixmap(QPixmap * p_)
{
    pix=p_;
}

void DemoSim::currentSnapshot(int n_) const
{
    n_--;
    pix->fill(Qt::white);
    QPainter p_(pix);
    p_.setBrush(Qt::red);
    int y=n_/10;
    int x=n_-y*10;
    for(int i=0;i<y;i++)
        for(int j=0;j<10;j++)
            p_.drawRect(j*_diameter,i*_diameter,_diameter,_diameter);
    for(int i=0;i<=x;i++)
        p_.drawRect(i*_diameter,y*_diameter,_diameter,_diameter);
}

//此函数有待重构
QSize DemoSim::calculationMinPixSize()
{
    int w_=_diameter*k;
    int h_=w_;
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
    p_.drawRect(x*_diameter,y*_diameter,_diameter,_diameter);
}

int DemoSim::frameAllNumber() const
{
    return 100;
}

void DemoSim::prepareRepaintPixmap()
{

}

void DemoSim::makeElementsBig(int factor)
{
    _diameter+=factor;
}

void DemoSim::setPixmapsize()
{

}
