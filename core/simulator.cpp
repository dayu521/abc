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

bool Simulator::nextFrame()
{

}

void Simulator::animationStart()
{

}

QWidget *Simulator::getUi()
{
    return new QWidget;
}
