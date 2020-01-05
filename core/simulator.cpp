#include "simulator.h"
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
}

QWidget *Simulator::getUi()
{
    return nullptr;
}
