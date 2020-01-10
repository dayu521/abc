#include "simulator.h"
#include<QWidget>
#include<QDebug>

Simulator::Simulator()
{

}

Simulator::~Simulator()
{

}

void Simulator::setPixmap(QPixmap *p)
{
    pix=p;
    p->fill();
}

QWidget *Simulator::getUi()
{
    return new QWidget;
}
