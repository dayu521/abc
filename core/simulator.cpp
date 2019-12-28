#include "simulator.h"
#include<QDebug>

Simulator::Simulator(QVector<int> *properties_):properties(properties_)
{
    if(properties==nullptr)
        qDebug()<<"properties为空";
}

void Simulator::makeElementsBig(int factor)
{
    std::for_each(properties->begin(),properties->end(),[=](int & x_){
//        x_+=x_*factor/10;
        x_+=factor;
    });
}

QWidget *Simulator::getUi()
{
    return nullptr;
}
