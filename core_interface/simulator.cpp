#include"simulator.h"
#include"datasource/wrap_far_away.h"
#include"animation/abstract_animation.h"

Simulator::Simulator(std::shared_ptr<FreezePainter> fp_, std::shared_ptr<WrapFarAway> fa_):
    animation{fp_},dataSource{fa_}
{

}

Simulator::~Simulator()
{

}

void Simulator::produceModelData()
{
    if(dataSource->status()==FAStatus::GodJob){
        animation->setInput(dataSource->getOutput());
        animation->initModelData();
        st=Status::HasModelData;
        return ;
    }
    st=Status::UnCertain;
}

void Simulator::clearModelData()
{
    animation->clearAllModelDatas();
}
