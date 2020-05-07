#include"simulator.h"
#include"datasource/far_away.h"
#include"animation/abstract_animation.h"

Simulator::Simulator(std::shared_ptr<FreezePainter> fp_,std::shared_ptr<FarAway> fa_):
    animation{fp_},dataSource{fa_}
{

}

Simulator::~Simulator()
{

}

void Simulator::clearModelData()
{
//    dataSource->
}
