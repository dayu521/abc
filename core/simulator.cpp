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

bool Simulator::hasAnimation() const
{
    return false;
}

void Simulator::nextFrame()
{

}

void Simulator::animationStart()
{

}

void Simulator::saveStatus()
{

}

void Simulator::restore()
{

}

QWidget *Simulator::getUi()
{
    return new QWidget;
}
