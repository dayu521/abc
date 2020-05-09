#include "rbtree_sim.h"
#include "animation/rbtree_model.h"
#include "datasource/rbdata.h"

Rbtree::Rbtree():Simulator(std::make_shared<RbtreeModel>(),std::make_shared<RbData>())
{

}

Rbtree::~Rbtree()
{

}

void Rbtree::setInputData(const std::vector<int> &v)
{
//    dataSource->setInput(v);
    st=Simulator::Status::UnCertain;
    Input a={RbData::Insert,1000};
    dataSource->setInput({a});
}

void Rbtree::clearModelData()
{
    animation->clearAllModelDatas();
    st=Simulator::Status::Empty;
}

void Rbtree::prepareReplay()
{
    animation->initModelData();
}

